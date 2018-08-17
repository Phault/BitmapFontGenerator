#include "imageeffects.h"

#include <QPainter>
#include <QRgb>
#include <QtMath>

#include "fastgaussianblur.h"

QImage ImageEffects::applyInnerShadow(const QImage &image, const QColor &color, int blurRadius, QPoint offset)
{
    // create a cutout of the image with the applied offset
    QImage tmp(image.size(), QImage::Format_ARGB32_Premultiplied);
    tmp.fill(color);
    QPainter tmpPainter(&tmp);
    tmpPainter.setCompositionMode(QPainter::CompositionMode_DestinationOut);
    tmpPainter.drawImage(-offset, image);

    tmpPainter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    tmpPainter.drawImage(0, 0, image);

    tmpPainter.end();

    tmp = FastGaussianBlur::applyBlur(tmp, blurRadius);

    // combine the shadow with the source image
    QImage result(tmp.size(), QImage::Format_ARGB32_Premultiplied);
    result.fill(Qt::transparent);
    tmpPainter.begin(&result);
    tmpPainter.setCompositionMode(QPainter::CompositionMode_Source);
    tmpPainter.drawImage(image.rect(), image);
    tmpPainter.setCompositionMode(QPainter::CompositionMode_SourceAtop);
    tmpPainter.drawImage(tmp.rect(), tmp);
    tmpPainter.end();

    return result;
}

QImage ImageEffects::applyDropShadow(const QImage &image, const QColor &color, int blurRadius, QPoint offset)
{
    // draw the image with an offset to a temporary image
    QImage tmp(image.size() + QSize(qAbs(offset.x()) + blurRadius, qAbs(offset.y()) + blurRadius), QImage::Format_ARGB32_Premultiplied);
    tmp.fill(0);
    QPainter tmpPainter(&tmp);
    tmpPainter.setCompositionMode(QPainter::CompositionMode_Source);
    tmpPainter.drawImage(offset, image);
    tmpPainter.end();

    tmp = FastGaussianBlur::applyBlur(tmp, blurRadius);

    // color the shadow
    tmpPainter.begin(&tmp);
    tmpPainter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    tmpPainter.fillRect(tmp.rect(), color);
    tmpPainter.end();

    // combine the shadow with the source image
    QImage result(tmp.size(), QImage::Format_ARGB32_Premultiplied);
    result.fill(Qt::transparent);
    tmpPainter.begin(&result);
    tmpPainter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    tmpPainter.drawImage(tmp.rect(), tmp);
    tmpPainter.drawImage(image.rect(), image);
    tmpPainter.end();

    return result;
}

QImage ImageEffects::applyOutline(const QImage &image, const QColor &color, int thickness)
{
    auto colorRgba = color.rgba();

    int kernelWidth = thickness * 2 + 1;
    QVector<qreal> kernel(kernelWidth * kernelWidth);

    qreal sqrThickness = thickness*thickness;
    for (int y = 0; y < kernelWidth; ++y)
    {
        for (int x = 0; x < kernelWidth; ++x)
        {
            auto sqrDistFromCenter = pow(x - thickness, 2) + pow(y - thickness, 2);
            auto val = thickness + 1 - thickness * sqrDistFromCenter / sqrThickness;
            val = qBound<qreal>(0, 1, val);
            kernel[y * kernelWidth + x] = val;
        }
    }

    QImage outlineImage(image.size() + QSize(thickness * 2, thickness * 2), QImage::Format_ARGB32);
    outlineImage.fill(Qt::transparent);
    auto outlineImagePixels = reinterpret_cast<QRgb*>(outlineImage.bits());
    auto outlineImageWidth = outlineImage.width();

    auto imagePixels = reinterpret_cast<const QRgb*>(image.bits());
    auto imageHeight = image.height();
    auto imageWidth = image.width();


    for (int y = 0; y < imageHeight; ++y)
    {
        for (int x = 0; x < imageWidth; ++x)
        {
            QRgb current = imagePixels[y * imageWidth + x];

            uchar currentA = uchar(qAlpha(current));

            if (currentA == 0)
                continue;

            for (int kernelY = 0; kernelY < kernelWidth; ++kernelY)
            {
                auto outlineImageY = y + kernelY;

                for (int kernelX = 0; kernelX < kernelWidth; ++kernelX)
                {
                    auto outlineImageX = x + kernelX;
                    auto kernelValue = kernel[kernelY * kernelWidth + kernelX];

                    if (kernelValue < 0.001)
                        continue;

                    if (kernelX != thickness || kernelY != thickness)
                    {
                        auto val = colorRgba;
                        auto colorA = currentA;
                        colorA *= qAlpha(val) / 255;
                        colorA *= kernelValue;
                        val = (val & 0x00FFFFFF) | uint(colorA) << 24;

                        auto cd = outlineImagePixels[outlineImageY * outlineImageWidth + outlineImageX];
                        if(qAlpha(val) > qAlpha(cd))
                            outlineImagePixels[outlineImageY * outlineImageWidth + outlineImageX] = val;
                    }
                }
            }
        }
    }

    auto result = image.copy(-thickness, -thickness, image.width() + thickness * 2, image.height() + thickness * 2);
    QPainter painter(&result);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    painter.drawImage(0, 0, outlineImage);
    painter.end();

    return result;
}
