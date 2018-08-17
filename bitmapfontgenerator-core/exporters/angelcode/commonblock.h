#ifndef COMMONBLOCK_H
#define COMMONBLOCK_H

#include <QDataStream>
#include <QJsonObject>
#include <QTextStream>
#include <QXmlStreamWriter>
#include "blocktype.h"


struct CommonBlock
{
    quint16 lineHeight = 0;
    quint16 base = 0;
    quint16 scaleW = 0;
    quint16 scaleH = 0;
    quint16 pages = 0;

    quint8 alphaChannel = 0;
    quint8 redChannel = 0;
    quint8 greenChannel = 0;
    quint8 blueChannel = 0;

    bool packed = false;

    friend QTextStream& operator<<(QTextStream &stream, const CommonBlock &block)
    {
        return stream << "common"
               << " lineHeight=" << block.lineHeight
               << " base=" << block.base
               << " scaleW=" << block.scaleW
               << " scaleH=" << block.scaleH
               << " pages=" << block.pages
               << " packed=" << int(block.packed)
               << " alphaChnl=" << block.alphaChannel
               << " redChnl=" << block.redChannel
               << " greenChnl=" << block.greenChannel
               << " blueChnl=" << block.blueChannel
               << "\n";
    }


    friend QXmlStreamWriter& operator<<(QXmlStreamWriter &stream, const CommonBlock &block)
    {
        stream.writeStartElement("common");
        stream.writeAttribute("lineHeight", QString::number(block.lineHeight));
        stream.writeAttribute("base", QString::number(block.base));
        stream.writeAttribute("scaleW", QString::number(block.scaleW));
        stream.writeAttribute("scaleH", QString::number(block.scaleH));
        stream.writeAttribute("pages", QString::number(block.pages));
        stream.writeAttribute("packed", QString::number(block.packed));
        stream.writeAttribute("alphaChnl", QString::number(block.alphaChannel));
        stream.writeAttribute("redChnl", QString::number(block.redChannel));
        stream.writeAttribute("greenChnl", QString::number(block.greenChannel));
        stream.writeAttribute("blueChnl", QString::number(block.blueChannel));
        stream.writeEndElement();
        return stream;
    }

    friend QJsonObject& operator<<(QJsonObject &parent, const CommonBlock &block)
    {
        QJsonObject jsonBlock;
        jsonBlock["lineHeight"] = block.lineHeight;
        jsonBlock["base"] = block.base;
        jsonBlock["scaleW"] = block.scaleW;
        jsonBlock["scaleH"] = block.scaleH;
        jsonBlock["pages"] = block.pages;
        jsonBlock["packed"] = int(block.packed);
        jsonBlock["alphaChnl"] = block.alphaChannel;
        jsonBlock["redChnl"] = block.redChannel;
        jsonBlock["greenChnl"] = block.greenChannel;
        jsonBlock["blueChnl"] = block.blueChannel;

        parent["common"] = jsonBlock;
        return parent;
    }

    friend QDataStream& operator<<(QDataStream &stream, const CommonBlock &block)
    {
        QByteArray blockData;
        QDataStream blockDataStream(&blockData, QIODevice::WriteOnly);
        blockDataStream.setByteOrder(QDataStream::LittleEndian);
        blockDataStream << block.lineHeight
                        << block.base
                        << block.scaleW
                        << block.scaleH
                        << block.pages
                        << quint8(block.packed) // no other used bitfields atm, so this is simple
                        << block.alphaChannel
                        << block.redChannel
                        << block.greenChannel
                        << block.blueChannel;

        stream << quint8(BlockType::Common)
               << quint32(blockData.length());

        stream.writeRawData(blockData.data(), blockData.length());

        return stream;
    }
};

#endif // COMMONBLOCK_H
