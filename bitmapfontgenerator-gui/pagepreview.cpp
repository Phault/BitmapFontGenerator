#include "pagepreview.h"
#include "ui_pagepreview.h"

#include <QDebug>
#include <QGraphicsPixmapItem>

PagePreview::PagePreview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PagePreview),
    mPreviewGraphics(),
    mBitmapFont()
{
    ui->setupUi(this);

    auto scene = new QGraphicsScene;
    scene->addItem(&mPreviewGraphics);
    ui->graphicsView->setScene(scene);

    connect(ui->pushButton, &QPushButton::clicked, this, &PagePreview::prevPage);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &PagePreview::nextPage);
    connect(ui->spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int value){
       this->setCurrentPage(value - 1);
    });
}

PagePreview::~PagePreview()
{
    delete ui;
}

const BitmapFont &PagePreview::bitmapFont() const
{
    return mBitmapFont;
}

void PagePreview::setBitmapFont(const BitmapFont &bmfont)
{
    mBitmapFont = bmfont;
    ui->spinBox->setMinimum(1);
    ui->spinBox->setMaximum(bmfont.pages().count());
    setCurrentPage(0);
}

int PagePreview::currentPage() const
{
    return mCurrentPage;
}

void PagePreview::setCurrentPage(int currentPage)
{
    mCurrentPage = currentPage;

    auto pageCount = mBitmapFont.pages().count();

    ui->label->setText(QString("%1/%2").arg(currentPage + 1).arg(pageCount));
    ui->pushButton->setEnabled(currentPage > 0);
    ui->pushButton_2->setEnabled(currentPage < pageCount - 1);
    ui->spinBox->setValue(currentPage + 1);

    if (currentPage >= 0 && currentPage < pageCount)
    {
        auto page = mBitmapFont.pages().at(currentPage);
        auto pixmap = QPixmap::fromImage(page);
        QPainter painter(&pixmap);
        painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
        painter.fillRect(pixmap.rect(), Qt::black);
        painter.end();
        mPreviewGraphics.setPixmap(pixmap);
    }
    else
        mPreviewGraphics.setPixmap(QPixmap());
}

void PagePreview::nextPage()
{
    setCurrentPage(std::min(currentPage() + 1, mBitmapFont.pages().count() - 1));
}

void PagePreview::prevPage()
{
    setCurrentPage(std::max(0, currentPage() - 1));
}
