#ifndef ANGELCODEFONT_H
#define ANGELCODEFONT_H

#include "bitmapfont.h"
#include "charsblock.h"
#include "commonblock.h"
#include "infoblock.h"
#include "kerningblock.h"
#include "pagesblock.h"

class Exporter;

struct AngelCodeFont
{
    InfoBlock info;
    CommonBlock common;
    PagesBlock pages;
    CharsBlock chars;
    KerningBlock kerning;

    AngelCodeFont () = default;
    AngelCodeFont (const BitmapFont &font, const Exporter &exporter);

    friend QTextStream& operator<<(QTextStream &stream, const AngelCodeFont &font)
    {
        return stream << font.info
                      << font.common
                      << font.pages
                      << font.chars
                      << font.kerning;
    }

    friend QXmlStreamWriter& operator<<(QXmlStreamWriter &stream, const AngelCodeFont &font)
    {
        stream.writeStartDocument();
        stream.writeStartElement("font");

        stream << font.info
               << font.common
               << font.pages
               << font.chars
               << font.kerning;

        stream.writeEndElement();
        stream.writeEndDocument();

        return stream;
    }

    friend QJsonObject& operator<<(QJsonObject &parent, const AngelCodeFont &font)
    {
        return parent << font.info
                      << font.common
                      << font.pages
                      << font.chars
                      << font.kerning;

    }

    friend QDataStream& operator<<(QDataStream &stream, const AngelCodeFont &font)
    {
        stream.setByteOrder(QDataStream::LittleEndian);

        static char header[4] = { 'B', 'M', 'F', 3};

        stream.writeRawData(header, 4);
        stream << font.info
               << font.common
               << font.pages
               << font.chars
               << font.kerning;

        return stream;
    }
};

#endif // ANGELCODEFONT_H
