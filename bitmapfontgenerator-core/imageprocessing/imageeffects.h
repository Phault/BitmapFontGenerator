#ifndef IMAGEEFFECTS_H
#define IMAGEEFFECTS_H

#include <QImage>

class ImageEffects
{
public:
    static QImage applyInnerShadow(const QImage &image, const QColor &color, int blurRadius, QPoint offset);
    static QImage applyDropShadow(const QImage &image, const QColor &color, int blurRadius, QPoint offset);
    static QImage applyOutline(const QImage &image, const QColor &color, int thickness);
};

#endif // IMAGEEFFECTS_H
