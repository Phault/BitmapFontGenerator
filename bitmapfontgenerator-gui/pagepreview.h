#ifndef PAGEPREVIEW_H
#define PAGEPREVIEW_H

#include <QGraphicsPixmapItem>
#include <QWidget>
#include <bitmapfont.h>

namespace Ui {
class PagePreview;
}

class PagePreview : public QWidget
{
    Q_OBJECT

public:
    explicit PagePreview(QWidget *parent = nullptr);
    ~PagePreview();

    const BitmapFont &bitmapFont() const;
    void setBitmapFont(const BitmapFont &bmfont);

    int currentPage() const;

public slots:
    void setCurrentPage(int currentPage);
    void nextPage();
    void prevPage();

private:
    Ui::PagePreview *ui;
    QGraphicsPixmapItem mPreviewGraphics;
    BitmapFont mBitmapFont;

    int mCurrentPage = 0;
};

#endif // PAGEPREVIEW_H
