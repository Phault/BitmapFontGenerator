#ifndef GLYPH_H
#define GLYPH_H

#include <QChar>
#include <QImage>
#include <QRect>
#include <QDebug>
#include <memory>

struct Glyph
{
    QChar character;
    QRect rect;
    QImage image;
    int page = -1;
    int xOffset = 0;
    int yOffset = 0;
    int xAdvance = 0;

    friend QDebug operator<<(QDebug stream, const Glyph& glyph)
    {
        return stream << "Char: " << glyph.character << "\n"
               << "Page: " << glyph.page << "\n"
               << "Rect: " << glyph.rect << "\n";
    }
};

#endif // GLYPH_H
