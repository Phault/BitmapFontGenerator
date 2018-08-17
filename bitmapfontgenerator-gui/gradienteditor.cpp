#include "gradienteditor.h"

#include <QPainter>
#include <QDebug>
#include <QPaintEvent>

GradientEditor::GradientEditor(QWidget *parent) :
    LinearGradientPreview(parent)
{

}

GradientEditor::~GradientEditor()
{

}

void GradientEditor::mousePressEvent(QMouseEvent *event)
{
}

void GradientEditor::mouseReleaseEvent(QMouseEvent *event)
{
}

void GradientEditor::mouseDoubleClickEvent(QMouseEvent *event)
{
    auto normalizedX = qreal(event->x()) / width();
    auto gradient = this->gradient();
    gradient.setColorAt(normalizedX, QColor(qrand() % 255, qrand() % 255, qrand() % 255));
    this->setGradient(gradient);
    event->accept();
}

void GradientEditor::mouseMoveEvent(QMouseEvent *event)
{

}

void GradientEditor::paintEvent(QPaintEvent *event)
{
    LinearGradientPreview::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::blue);
    painter.drawPie(-10, -10, 50, 50, 70 * 16, 40 * 16);
//    painter.fillRect(event->rect(), Qt::green);
}
