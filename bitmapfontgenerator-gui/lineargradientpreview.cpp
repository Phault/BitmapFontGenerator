#include "lineargradientpreview.h"

#include <QList>
#include <QPainter>

LinearGradientPreview::LinearGradientPreview(QWidget *parent) :
    QWidget(parent)
{
    QLinearGradient gradient;
    gradient.setColorAt(0, Qt::black);
    gradient.setColorAt(1, Qt::white);
    setGradient(gradient);
}

LinearGradientPreview::~LinearGradientPreview()
{

}

QLinearGradient LinearGradientPreview::gradient() const
{
    return mGradient;
}

void LinearGradientPreview::setGradient(const QLinearGradient &gradient)
{
    mGradient = gradient;
    mGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    mGradient.setStart(0, 0);
    mGradient.setFinalStop(1, 0);
    repaint();
}

void LinearGradientPreview::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(event->rect(), mGradient);
}
