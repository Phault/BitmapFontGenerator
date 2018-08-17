#ifndef KERNINGBLOCK_H
#define KERNINGBLOCK_H

#include <QDataStream>
#include <QJsonArray>
#include <QJsonObject>
#include <QMap>
#include <QString>
#include <QTextStream>
#include <QXmlStreamWriter>
#include "blocktype.h"


struct KerningBlock
{
    QMap<QPair<QChar, QChar>, qint16> pairs;

    KerningBlock () = default;

    KerningBlock(const QMap<QPair<QChar, QChar>, qreal> &pairsF)
    {
        for (auto iterator = pairsF.constBegin(); iterator != pairsF.constEnd(); ++iterator)
        {
            auto& pair = iterator.key();
            auto amount = qint16(qRound(iterator.value()));

            if (amount != 0)
                pairs.insert(pair, amount);
        }
    }

    friend QTextStream& operator<<(QTextStream &stream, const KerningBlock &block)
    {
        if (block.pairs.count() == 0)
            return stream;

        stream << "kernings count=" << block.pairs.count() << "\n";

        for (auto iterator = block.pairs.constBegin(); iterator != block.pairs.constEnd(); ++iterator)
        {
            auto& pair = iterator.key();

            stream << "kerning"
                   << " first=" << pair.first.unicode()
                   << " second=" << pair.second.unicode()
                   << " amount=" << iterator.value()
                   << "\n";
        }

        return stream;
    }

    friend QXmlStreamWriter& operator<<(QXmlStreamWriter &stream, const KerningBlock &block)
    {
        stream.writeStartElement("kernings");
        stream.writeAttribute("count", QString::number(block.pairs.count()));

        for (auto iterator = block.pairs.constBegin(); iterator != block.pairs.constEnd(); ++iterator)
        {
            const auto& pair = iterator.key();

            stream.writeStartElement("kerning");
            stream.writeAttribute("first", QString::number(pair.first.unicode()));
            stream.writeAttribute("second", QString::number(pair.second.unicode()));
            stream.writeAttribute("amount", QString::number(iterator.value()));
            stream.writeEndElement();
        }

        stream.writeEndElement();
        return stream;
    }

    friend QJsonObject& operator<<(QJsonObject &parent, const KerningBlock &block)
    {
        QJsonArray kerningPairs;

        for (auto iterator = block.pairs.constBegin(); iterator != block.pairs.constEnd(); ++iterator)
        {
            const auto& pair = iterator.key();

            QJsonObject jsonPair;
            jsonPair["first"] = pair.first.unicode();
            jsonPair["second"] = pair.second.unicode();
            jsonPair["amount"] = iterator.value();

            kerningPairs.append(jsonPair);
        }

        parent["kernings"] = kerningPairs;
        return parent;
    }

    friend QDataStream& operator<<(QDataStream &stream, const KerningBlock &block)
    {
        if (block.pairs.count() == 0)
            return stream;

        QByteArray blockData;
        QDataStream blockDataStream(&blockData, QIODevice::WriteOnly);
        blockDataStream.setByteOrder(QDataStream::LittleEndian);

        for (auto iterator = block.pairs.constBegin(); iterator != block.pairs.constEnd(); ++iterator)
        {
            const auto& pair = iterator.key();
            blockDataStream << quint32(pair.first.unicode())
                            << quint32(pair.second.unicode())
                            << qint16(iterator.value());
        }

        stream << quint8(BlockType::KerningPairs)
               << quint32(blockData.length());

        stream.writeRawData(blockData.data(), blockData.length());

        return stream;
    }
};

#endif // KERNINGBLOCK_H
