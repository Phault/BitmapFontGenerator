#ifndef FASTGAUSSIANBLUR_H
#define FASTGAUSSIANBLUR_H

#include <QImage>

class FastGaussianBlur
{
public:
    static QImage applyBlur(const QImage &image, int blurRadius);

private:
    static QVector<int> boxesForGauss(qreal sigma, int amount);
    static void applyBoxBlur(QImage &source, QImage &target, int blurRadius);
    static void applyBlurH(QImage &source, QImage &target, int blurRadius);
    static void applyBlurV(QImage &source, QImage &target, int blurRadius);
};

#endif // FASTGAUSSIANBLUR_H
