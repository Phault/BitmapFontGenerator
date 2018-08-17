#include "angelcodefont.h"

#include <exporters/exporter.h>

AngelCodeFont::AngelCodeFont (const BitmapFont &font, const Exporter &exporter)
{
    info.unicode = true;
    info.smooth = false;
    info.fontName = font.name;
    info.fontSize = qint16(-font.originalFont.pixelSize());
    info.antiAliasing = quint8(font.antiAliasing);
    info.padding = font.padding;
    info.spacingHorizontal = quint8(font.spacingHorizontal);
    info.spacingVertical = quint8(font.spacingVertical);
    info.outline = 0;

    common.lineHeight = quint16(font.lineSpacing);
    common.base = quint16(font.baseLine);
    common.scaleW = quint16(font.pages().at(0).width());
    common.scaleH = quint16(font.pages().at(0).height());
    common.pages = quint16(font.pages().size());
    common.packed = 0;
    common.alphaChannel = 1;

    for (int i = 0; i < font.pages().length(); ++i)
        pages.fileNames.append(exporter.getPagePath(i, font.pages().length()).fileName());

    chars = font.glyphs();
    kerning = font.kerningPairs;
}
