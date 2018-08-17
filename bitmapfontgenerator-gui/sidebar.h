#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>

class QGroupBox;

namespace Ui {
class Sidebar;
}

class Sidebar : public QWidget
{
    Q_OBJECT

public:
    explicit Sidebar(QWidget *parent = nullptr);
    ~Sidebar();

    QGroupBox *addWidget(const QString &title, QWidget *widget);

private:
    Ui::Sidebar *ui;
};

#endif // SIDEBAR_H
