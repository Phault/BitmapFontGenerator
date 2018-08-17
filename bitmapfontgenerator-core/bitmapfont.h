#ifndef BITMAPFONT_H
#define BITMAPFONT_H

#include "glyph.h"
#include "padding.h"
#include <QRawFont>

class BitmapFont
{
public:
    BitmapFont() = default;
    BitmapFont(QList<QImage> pages, QList<Glyph> glyphs);

    const QList<QImage>& pages() const;
    const QList<Glyph>& glyphs() const;

    QRawFont originalFont;
    QString name = "BitmapFont";
    int lineSpacing = 0;
    int baseLine = 0;
    QMap<QPair<QChar, QChar>, qreal> kerningPairs;
    Padding padding {0, 0, 0, 0};
    int spacingHorizontal = 1;
    int spacingVertical = 1;
    bool antiAliasing = true;

private:
    QList<QImage> mPages;
    QList<Glyph> mGlyphs;
};

#endif // BITMAPFONT_H
