#ifndef CHARSBLOCK_H
#define CHARSBLOCK_H

#include <QDataStream>
#include <QTextStream>
#include <QString>
#include <glyph.h>
#include <QXmlStreamWriter>
#include <QJsonObject>
#include <QJsonArray>
#include "blocktype.h"


struct CharsBlock
{
    QList<Glyph> glyphs;

    CharsBlock () = default;

    CharsBlock (const QList<Glyph> &glyphs) :
        glyphs(glyphs)
    {
    }

    friend QTextStream& operator<<(QTextStream &stream, const CharsBlock &block)
    {
        stream << "chars count=" << block.glyphs.length() << "\n";

        for (const auto& glyph : block.glyphs)
        {
            stream << "char"
                   << " id=" << glyph.character.unicode()
                   << " x=" << glyph.rect.x()
                   << " y=" << glyph.rect.y()
                   << " width=" << glyph.rect.width()
                   << " height=" << glyph.rect.height()
                   << " xoffset=" << glyph.xOffset
                   << " yoffset=" << glyph.yOffset
                   << " xadvance=" << glyph.xAdvance
                   << " page=" << glyph.page
                   << " chnl=" << 15
                   << "\n";
        }

        return stream;
    }

    friend QXmlStreamWriter& operator<<(QXmlStreamWriter &stream, const CharsBlock &block)
    {
        stream.writeStartElement("chars");
        stream.writeAttribute("count", QString::number(block.glyphs.length()));

        for (const auto& glyph : block.glyphs)
        {
            stream.writeStartElement("char");
            stream.writeAttribute("id", QString::number(glyph.character.unicode()));
            stream.writeAttribute("x", QString::number(glyph.rect.x()));
            stream.writeAttribute("y", QString::number(glyph.rect.y()));
            stream.writeAttribute("width", QString::number(glyph.rect.width()));
            stream.writeAttribute("height", QString::number(glyph.rect.height()));
            stream.writeAttribute("xoffset", QString::number(glyph.xOffset));
            stream.writeAttribute("yoffset", QString::number(glyph.yOffset));
            stream.writeAttribute("xadvance", QString::number(glyph.xAdvance));
            stream.writeAttribute("page", QString::number(glyph.page));
            stream.writeAttribute("chnl", QString::number(15));
            stream.writeEndElement();
        }

        stream.writeEndElement();
        return stream;
    }

    friend QJsonObject& operator<<(QJsonObject &parent, const CharsBlock &block)
    {
        QJsonArray chars;

        for (const auto& glyph : block.glyphs)
        {
            QJsonObject jsonChar;
            jsonChar["id"] = glyph.character.unicode();
            jsonChar["x"] = glyph.rect.x();
            jsonChar["y"] = glyph.rect.y();
            jsonChar["width"] = glyph.rect.width();
            jsonChar["height"] = glyph.rect.height();
            jsonChar["xoffset"] = glyph.xOffset;
            jsonChar["yoffset"] = glyph.yOffset;
            jsonChar["xadvance"] = glyph.xAdvance;
            jsonChar["page"] = glyph.page;
            jsonChar["chnl"] = 15;

            chars.append(jsonChar);
        }

        parent["chars"] = chars;
        return parent;
    }

    friend QDataStream& operator<<(QDataStream &stream, const CharsBlock &block)
    {
        QByteArray blockData;
        QDataStream blockDataStream(&blockData, QIODevice::WriteOnly);
        blockDataStream.setByteOrder(QDataStream::LittleEndian);

        for (const auto& glyph : block.glyphs)
        {
            blockDataStream << quint32(glyph.character.unicode())
                            << quint16(glyph.rect.x())
                            << quint16(glyph.rect.y())
                            << quint16(glyph.rect.width())
                            << quint16(glyph.rect.height())
                            << qint16(glyph.xOffset)
                            << qint16(glyph.yOffset)
                            << qint16(glyph.xAdvance)
                            << quint8(glyph.page)
                            << quint8(15);
        }

        stream << quint8(BlockType::Chars)
               << quint32(blockData.length());

        stream.writeRawData(blockData.data(), blockData.length());

        return stream;
    }
};

#endif // CHARSBLOCK_H
