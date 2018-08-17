#ifndef LINEARGRADIENTPREVIEW_H
#define LINEARGRADIENTPREVIEW_H

#include <QWidget>

class LinearGradientPreview : public QWidget
{
    Q_OBJECT

public:
    explicit LinearGradientPreview(QWidget *parent = nullptr);
    ~LinearGradientPreview() override;

    QLinearGradient gradient() const;
    void setGradient(const QLinearGradient &gradient);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QLinearGradient mGradient;
};

#endif // LINEARGRADIENTPREVIEW_H
