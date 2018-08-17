#include "sidebar.h"
#include "ui_sidebar.h"

#include <QGroupBox>

Sidebar::Sidebar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sidebar)
{
    ui->setupUi(this);
}

Sidebar::~Sidebar()
{
    delete ui;
}

QGroupBox *Sidebar::addWidget(const QString &title, QWidget *widget)
{
    QGroupBox *group = new QGroupBox(title);
    group->setLayout(new QBoxLayout(QBoxLayout::TopToBottom));
    group->layout()->addWidget(widget);

    auto container = static_cast<QVBoxLayout*>(ui->contents->layout());
    container->insertWidget(container->count() - 1, group);

    return group;
}
