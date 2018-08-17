#include "fontutils.h"

#include <QHash>
#include <QChar>
#include <QRawFont>
#include <QDataStream>
#include <QSet>

// Partly inspired by https://github.com/nodebox/opentype.js/blob/master/src/tables/kern.js

QHash<QPair<int, int>, qreal> FontUtils::getKerningPairs(const QRawFont &font, const QSet<quint32> &glyphIndexes, bool ignoreZero)
{
    const auto kerningPairsLogical = getKerningPairsInLogicalUnits(font, glyphIndexes, ignoreZero);

    QHash<QPair<int, int>, qreal> kerningPairs;
    kerningPairs.reserve(kerningPairsLogical.size());

    const auto fontHeight = font.pixelSize();
    const auto unitsPerEm = font.unitsPerEm();

    for (auto iterator = kerningPairsLogical.constBegin(); iterator != kerningPairsLogical.constEnd(); ++iterator)
    {
        auto kerningResult = iterator.value() / unitsPerEm * fontHeight;
        kerningPairs.insert(iterator.key(), kerningResult);
    }

    return kerningPairs;
}

QHash<QPair<int, int>, int> FontUtils::getKerningPairsInLogicalUnits(const QRawFont &font, const QSet<quint32> &glyphIndexes, bool ignoreZero)
{
    auto kerningTable = font.fontTable("kern");

    QDataStream stream(kerningTable);
    stream.setByteOrder(QDataStream::BigEndian);

    quint16 version;
    stream >> version;

    if (version == 0)
        return getOpenTypeKerningPairs(stream, glyphIndexes, ignoreZero);
    else if (version == 1)
        return getTrueTypeKerningPairs(stream, glyphIndexes, ignoreZero);
    else
        throw std::invalid_argument("The kern table version is not supported.");
}

// https://docs.microsoft.com/en-us/typography/opentype/spec/kern
QHash<QPair<int, int>, int> FontUtils::getOpenTypeKerningPairs(QDataStream &stream, const QSet<quint32> &glyphIndexes, bool ignoreZero)
{
    quint16 nTables; // a font can have multiple kern tables. the kerning values should simply be summed.
    stream >> nTables;

    QHash<QPair<int, int>, int> kerningPairs;

    for (quint16 i = 0; i < nTables; ++i)
    {
        uint16_t subTableVersion;
        stream >> subTableVersion;

        if (subTableVersion != 0) // not supported
            continue;

        // skip subtableLength and subtableCoverage
        // todo: check whether format #2 is used at all or atleast at a check for it
        stream.skipRawData(sizeof(quint16) * 2);

        quint16 numPairs;
        stream >> numPairs;

        // skip searchRange, entrySelector and rangeShift
        stream.skipRawData(sizeof(quint16) * 3);

        for (int j = 0; j < numPairs; ++j)
        {
            quint16 leftIndex;
            quint16 rightIndex;
            qint16 value;
            stream >> leftIndex >> rightIndex >> value;

            if (!ignoreZero || value != 0)
            {
                if (glyphIndexes.contains(leftIndex) && glyphIndexes.contains(rightIndex))
                {
                    QPair<int, int> pair(leftIndex, rightIndex);
                    kerningPairs[pair] += value;
                }
            }
        }
    }

    return kerningPairs;
}

// https://developer.apple.com/fonts/TrueType-Reference-Manual/RM06/Chap6kern.html
QHash<QPair<int, int>, int> FontUtils::getTrueTypeKerningPairs(QDataStream &stream, const QSet<quint32> &glyphIndexes, bool ignoreZero)
{
    // version is actually a uint32 on mac, so we skip the remaining bits
    stream.skipRawData(sizeof(quint16));

    quint32 nTables;
    stream >> nTables;

    QHash<QPair<int, int>, int> kerningPairs;

    for (quint32 i = 0; i < nTables; ++i)
    {
        // skip length
        stream.skipRawData(sizeof(quint32));

        quint16 coverage;
        stream >> coverage;
        quint16 format = coverage & 0xFF;

        // skip tupleIndex
        stream.skipRawData(sizeof(quint16));

        // todo: are 1-3 used and should they be supported?
        if (format == 0)
        {
            quint16 numPairs;
            stream >> numPairs;

            // skip searchRange, entrySelector and rangeShift
            stream.skipRawData(sizeof(quint16) * 3);

            for (int j = 0; j < numPairs; ++j)
            {
                quint16 leftIndex;
                quint16 rightIndex;
                qint16 value;
                stream >> leftIndex >> rightIndex >> value;

                if (!ignoreZero || value != 0)
                {
                    if (glyphIndexes.contains(leftIndex) && glyphIndexes.contains(rightIndex))
                    {
                        QPair<int, int> pair(leftIndex, rightIndex);
                        kerningPairs[pair] += value;
                    }
                }
            }
        }
    }

    return kerningPairs;
}
