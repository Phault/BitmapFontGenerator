#ifndef PAGESBLOCK_H
#define PAGESBLOCK_H

#include <QDataStream>
#include <QVector>
#include <QString>
#include <QTextStream>
#include <QXmlStreamWriter>
#include <QJsonArray>
#include <QVariant>
#include <QJsonObject>
#include <bitmapfont.h>
#include "blocktype.h"


struct PagesBlock
{
    QStringList fileNames;

    PagesBlock () = default;

    PagesBlock(std::initializer_list<QString> pages) :
        fileNames(pages)
    {

    }

    friend QTextStream& operator<<(QTextStream &stream, const PagesBlock &block)
    {
        for (int i = 0; i < block.fileNames.length(); i++)
        {
            stream << "page"
                   << " id=" << i
                   << " file=\"" << block.fileNames[i] << "\""
                   << "\n";
        }

        return stream;
    }


    friend QXmlStreamWriter& operator<<(QXmlStreamWriter &stream, const PagesBlock &block)
    {
        stream.writeStartElement("pages");
        for (int i = 0; i < block.fileNames.length(); i++)
        {
            stream.writeStartElement("page");
            stream.writeAttribute("id", QString::number(i));
            stream.writeAttribute("file", block.fileNames[i]);
            stream.writeEndElement();
        }
        stream.writeEndElement();
        return stream;
    }

    friend QJsonObject& operator<<(QJsonObject &parent, const PagesBlock &block)
    {
        parent["pages"] = QJsonArray::fromStringList(block.fileNames);
        return parent;
    }

    friend QDataStream& operator<<(QDataStream &stream, const PagesBlock &block)
    {
        QByteArray blockData;
        QDataStream blockDataStream(&blockData, QIODevice::WriteOnly);
        blockDataStream.setByteOrder(QDataStream::LittleEndian);

        for (const auto& fileName : block.fileNames)
        {
            auto stdString = fileName.toStdString();
            blockDataStream.writeRawData(stdString.data(), int(stdString.length() + 1));
        }

        stream << quint8(BlockType::Pages)
               << quint32(blockData.length());

        stream.writeRawData(blockData.data(), blockData.length());

        return stream;
    }
};

#endif // PAGESBLOCK_H
