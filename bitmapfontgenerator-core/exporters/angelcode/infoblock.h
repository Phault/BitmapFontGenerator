#ifndef INFOBLOCK_H
#define INFOBLOCK_H

#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <QTextStream>
#include <QXmlStreamWriter>
#include <padding.h>

#include <QDataStream>
#include "blocktype.h"


struct InfoBlock
{
    QString fontName;
    qint16 fontSize = 0;
    quint8 charSet = 0;
    quint16 stretchH = 100;
    quint8 antiAliasing = 0;
    Padding padding;
    quint8 spacingHorizontal = 0;
    quint8 spacingVertical = 0;
    quint8 outline = 0;

    bool smooth = false;
    bool unicode = false;
    bool italic = false;
    bool bold = false;
    bool fixedHeight = false;

    friend QTextStream& operator<<(QTextStream &stream, const InfoBlock &block)
    {
        return stream
               << "info"
               << " face=\"" << block.fontName << "\""
               << " size=" << block.fontSize
               << " bold=" << int(block.bold)
               << " italic=" << int(block.italic)
               << " charset=" << "\"\""
               << " unicode=" << int(block.unicode)
               << " stretchH=" << block.stretchH
               << " smooth=" << int(block.smooth)
               << " aa=" << block.antiAliasing
               << " padding=" << QString("%1,%2,%3,%4")
                                  .arg(block.padding.top)
                                  .arg(block.padding.right)
                                  .arg(block.padding.bottom)
                                  .arg(block.padding.left)
               << " spacing=" << QString("%1,%2")
                                  .arg(block.spacingHorizontal)
                                  .arg(block.spacingVertical)
               << " outline=" << block.outline
               << "\n";
    }

    friend QXmlStreamWriter& operator<<(QXmlStreamWriter &stream, const InfoBlock &block)
    {
        stream.writeStartElement("info");
        stream.writeAttribute("face", block.fontName);
        stream.writeAttribute("size", QString::number(block.fontSize));
        stream.writeAttribute("bold", QString::number(block.bold));
        stream.writeAttribute("italic", QString::number(block.italic));
        // fixme: charset should be a string
        stream.writeAttribute("charset", QString::number(block.charSet));
        stream.writeAttribute("unicode", QString::number(block.unicode));
        stream.writeAttribute("stretchH", QString::number(block.stretchH));
        stream.writeAttribute("smooth", QString::number(block.smooth));
        stream.writeAttribute("aa", QString::number(block.antiAliasing));
        stream.writeAttribute("padding", QString("%1,%2,%3,%4")
                                          .arg(block.padding.top)
                                          .arg(block.padding.right)
                                          .arg(block.padding.bottom)
                                          .arg(block.padding.left));
        stream.writeAttribute("spacing", QString("%1,%2")
                                          .arg(block.spacingHorizontal)
                                          .arg(block.spacingVertical));
        stream.writeAttribute("outline", QString::number(block.outline));
        stream.writeEndElement();
        return stream;
    }

    friend QJsonObject& operator<<(QJsonObject &parent, const InfoBlock &block)
    {
        QJsonObject jsonBlock;
        jsonBlock["face"] = block.fontName;
        jsonBlock["size"] = block.fontSize;
        jsonBlock["bold"] = int(block.bold);
        jsonBlock["italic"] = int(block.italic);
        // fixme: charset should be a string
        jsonBlock["charset"] = block.charSet;
        jsonBlock["unicode"] = int(block.unicode);
        jsonBlock["stretchH"] = block.stretchH;
        jsonBlock["smooth"] = int(block.smooth);
        jsonBlock["aa"] = block.antiAliasing;
        jsonBlock["padding"] = QJsonArray({ block.padding.top, block.padding.right, block.padding.bottom, block.padding.left });
        jsonBlock["spacing"] = QJsonArray({ block.spacingHorizontal, block.spacingVertical });
        jsonBlock["outline"] = block.fontSize;

        parent["info"] = jsonBlock;
        return parent;
    }

    friend QDataStream& operator<<(QDataStream &stream, const InfoBlock &block)
    {
        quint8 bitField = 0;
        bitField |= block.smooth << 7;
        bitField |= block.unicode << 6;
        bitField |= block.italic << 5;
        bitField |= block.bold << 4;
        bitField |= block.fixedHeight << 3;

        QByteArray blockData;
        QDataStream blockDataStream(&blockData, QIODevice::WriteOnly);
        blockDataStream.setByteOrder(QDataStream::LittleEndian);
        blockDataStream << block.fontSize
                        << bitField
                        << block.charSet
                        << block.stretchH
                        << block.antiAliasing
                        << quint8(block.padding.top)
                        << quint8(block.padding.right)
                        << quint8(block.padding.bottom)
                        << quint8(block.padding.left)
                        << block.spacingHorizontal
                        << block.spacingVertical
                        << block.outline;

        blockDataStream.writeRawData(block.fontName.toStdString().data(), block.fontName.length() + 1);

        stream << quint8(BlockType::Info)
               << quint32(blockData.length());

        stream.writeRawData(blockData.data(), blockData.length());

        return stream;
    }
};

#endif // INFOBLOCK_H
