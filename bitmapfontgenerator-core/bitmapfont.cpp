#include "bitmapfont.h"

BitmapFont::BitmapFont(QList<QImage> pages, QList<Glyph> glyphs) :
    mPages(pages),
    mGlyphs(glyphs)
{

}

const QList<QImage> &BitmapFont::pages() const
{
    return mPages;
}

const QList<Glyph> &BitmapFont::glyphs() const
{
    return mGlyphs;
}
