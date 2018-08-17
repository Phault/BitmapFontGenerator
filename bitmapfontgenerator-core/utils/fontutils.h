#ifndef FONTUTILS_H
#define FONTUTILS_H

#include <QHash>
#include <QPair>
class QRawFont;
class QDataStream;

class FontUtils
{
public:
    static QHash<QPair<int, int>, qreal> getKerningPairs(const QRawFont &font, const QSet<quint32> &glyphIndexes, bool ignoreZero = true);
    static QHash<QPair<int, int>, int> getKerningPairsInLogicalUnits(const QRawFont &font, const QSet<quint32> &glyphIndexes, bool ignoreZero = true);

private:
    static QHash<QPair<int, int>, int> getOpenTypeKerningPairs(QDataStream &stream, const QSet<quint32> &glyphIndexes, bool ignoreZero = true);
    static QHash<QPair<int, int>, int> getTrueTypeKerningPairs(QDataStream &stream, const QSet<quint32> &glyphIndexess, bool ignoreZero = true);
};

#endif // FONTUTILS_H
