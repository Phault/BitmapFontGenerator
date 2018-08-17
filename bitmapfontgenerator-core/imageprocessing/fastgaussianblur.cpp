#include "fastgaussianblur.h"
#include <QRgb>
#include <QtMath>

// Code is based on http://blog.ivank.net/fastest-gaussian-blur.html

QImage FastGaussianBlur::applyBlur(const QImage &image, int blurRadius)
{
    auto boxes = boxesForGauss(blurRadius, 3);
    auto source = image.convertToFormat(QImage::Format_ARGB32_Premultiplied);
    auto target = source;

    applyBoxBlur(source, target, (boxes[0]-1) / 2);
    applyBoxBlur(target, source, (boxes[1]-1) / 2);
    applyBoxBlur(source, target, (boxes[2]-1) / 2);
    return target;
}

QVector<int> FastGaussianBlur::boxesForGauss(qreal sigma, int amount)
{
    auto wIdeal = qSqrt((12*sigma*sigma/amount)+1);
    auto wl = qFloor(wIdeal);

    if (wl%2 == 0)
        wl--;

    auto wu = wl+2;

    auto mIdeal = (12*sigma*sigma - amount*wl*wl - 4*amount*wl - 3*amount) / (-4*wl-4);
    auto m = qRound(mIdeal);

    QVector<int> result;

    for (int i=0; i<amount; i++)
        result += i < m ? wl : wu;

    return result;
}

void FastGaussianBlur::applyBoxBlur(QImage &source, QImage &target, int blurRadius)
{
    applyBlurH(target, source, blurRadius);
    applyBlurV(source, target, blurRadius);
}

void FastGaussianBlur::applyBlurH(QImage &source, QImage &target, int blurRadius)
{
    auto accumalatorAverage = 1.0f / (blurRadius + blurRadius + 1);

    const auto width = source.width();
    const auto height = source.height();
    auto sourcePixels = reinterpret_cast<QRgb*>(source.bits());
    auto targetPixels = reinterpret_cast<QRgb*>(target.bits());

    for (int y = 0; y < height; ++y)
    {
        auto ti = y * width,
                li = ti,
                ri = ti + blurRadius;

        QRgb firstValue = sourcePixels[ti];
        QRgb lastValue = sourcePixels[ti + width - 1];
        auto red = (blurRadius + 1) * qRed(firstValue);
        auto green = (blurRadius + 1) * qGreen(firstValue);
        auto blue = (blurRadius + 1) * qGreen(firstValue);
        auto alpha = (blurRadius + 1) * qAlpha(firstValue);

        for (int j = 0; j < blurRadius; ++j)
        {
            red += qRed(sourcePixels[ti + j]);
            green += qGreen(sourcePixels[ti + j]);
            blue += qBlue(sourcePixels[ti + j]);
            alpha += qAlpha(sourcePixels[ti + j]);
        }

        for (int j = 0; j <= blurRadius; ++j)
        {
            red += qRed(sourcePixels[ri]) - qRed(firstValue);
            green += qGreen(sourcePixels[ri]) - qGreen(firstValue);
            blue += qBlue(sourcePixels[ri]) - qBlue(firstValue);
            alpha += qAlpha(sourcePixels[ri]) - qAlpha(firstValue);
            ri++;
            targetPixels[ti++] = qRgba(qRound(red * accumalatorAverage),
                                       qRound(green * accumalatorAverage),
                                       qRound(blue * accumalatorAverage),
                                       qRound(alpha * accumalatorAverage));
        }

        for (int j = blurRadius + 1; j < width - blurRadius; ++j)
        {
            red += qRed(sourcePixels[ri]) - qRed(sourcePixels[li]);
            green += qGreen(sourcePixels[ri]) - qGreen(sourcePixels[li]);
            blue += qBlue(sourcePixels[ri]) - qBlue(sourcePixels[li]);
            alpha += qAlpha(sourcePixels[ri]) - qAlpha(sourcePixels[li]);
            ri++;
            li++;
            targetPixels[ti++] = qRgba(qRound(red * accumalatorAverage),
                                       qRound(green * accumalatorAverage),
                                       qRound(blue * accumalatorAverage),
                                       qRound(alpha * accumalatorAverage));
        }

        for (int j = width - blurRadius; j < width; ++j)
        {
            red += qRed(lastValue) - qRed(sourcePixels[li]);
            green += qGreen(lastValue) - qGreen(sourcePixels[li]);
            blue += qBlue(lastValue) - qBlue(sourcePixels[li]);
            alpha += qAlpha(lastValue) - qAlpha(sourcePixels[li]);
            li++;
            targetPixels[ti++] = qRgba(qRound(red * accumalatorAverage),
                                       qRound(green * accumalatorAverage),
                                       qRound(blue * accumalatorAverage),
                                       qRound(alpha * accumalatorAverage));
        }
    }
}

void FastGaussianBlur::applyBlurV(QImage &source, QImage &target, int blurRadius)
{
    auto accumalatorAverage = 1.0f / (blurRadius + blurRadius + 1);

    const auto width = source.width();
    const auto height = source.height();
    auto sourcePixels = reinterpret_cast<QRgb*>(source.bits());
    auto targetPixels = reinterpret_cast<QRgb*>(target.bits());

    for (int x = 0; x < width; ++x)
    {
        auto ti = x,
                li = ti,
                ri = ti + blurRadius * width;

        QRgb firstValue = sourcePixels[ti];
        QRgb lastValue = sourcePixels[ti + width * (height - 1)];
        auto red = (blurRadius + 1) * qRed(firstValue);
        auto green = (blurRadius + 1) * qGreen(firstValue);
        auto blue = (blurRadius + 1) * qGreen(firstValue);
        auto alpha = (blurRadius + 1) * qAlpha(firstValue);

        for (int j = 0; j < blurRadius; ++j)
        {
            red += qRed(sourcePixels[ti + j * width]);
            green += qGreen(sourcePixels[ti + j * width]);
            blue += qBlue(sourcePixels[ti + j * width]);
            alpha += qAlpha(sourcePixels[ti + j * width]);
        }

        for (int j = 0; j <= blurRadius; ++j)
        {
            red += qRed(sourcePixels[ri]) - qRed(firstValue);
            green += qGreen(sourcePixels[ri]) - qGreen(firstValue);
            blue += qBlue(sourcePixels[ri]) - qBlue(firstValue);
            alpha += qAlpha(sourcePixels[ri]) - qAlpha(firstValue);

            targetPixels[ti] = qRgba(qRound(red * accumalatorAverage),
                                       qRound(green * accumalatorAverage),
                                       qRound(blue * accumalatorAverage),
                                       qRound(alpha * accumalatorAverage));

            ri += width;
            ti += width;
        }

        for (int j = blurRadius + 1; j < height - blurRadius; ++j)
        {
            red += qRed(sourcePixels[ri]) - qRed(sourcePixels[li]);
            green += qGreen(sourcePixels[ri]) - qGreen(sourcePixels[li]);
            blue += qBlue(sourcePixels[ri]) - qBlue(sourcePixels[li]);
            alpha += qAlpha(sourcePixels[ri]) - qAlpha(sourcePixels[li]);

            targetPixels[ti] = qRgba(qRound(red * accumalatorAverage),
                                       qRound(green * accumalatorAverage),
                                       qRound(blue * accumalatorAverage),
                                       qRound(alpha * accumalatorAverage));

            li += width;
            ri += width;
            ti += width;
        }

        for (int j = height - blurRadius; j < height; ++j)
        {
            red += qRed(lastValue) - qRed(sourcePixels[li]);
            green += qGreen(lastValue) - qGreen(sourcePixels[li]);
            blue += qBlue(lastValue) - qBlue(sourcePixels[li]);
            alpha += qAlpha(lastValue) - qAlpha(sourcePixels[li]);

            targetPixels[ti] = qRgba(qRound(red * accumalatorAverage),
                                       qRound(green * accumalatorAverage),
                                       qRound(blue * accumalatorAverage),
                                       qRound(alpha * accumalatorAverage));

            li += width;
            ti += width;
        }
    }
}
