#ifndef GRADIENTEDITOR_H
#define GRADIENTEDITOR_H

#include "lineargradientpreview.h"

#include <QWidget>

class GradientEditor : public LinearGradientPreview
{
    Q_OBJECT

public:
    explicit GradientEditor(QWidget *parent = nullptr);
    ~GradientEditor() override;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
};

#endif // GRADIENTEDITOR_H
