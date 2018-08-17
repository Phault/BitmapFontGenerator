#ifndef EFFECTCONTEXT_H
#define EFFECTCONTEXT_H

#include <QRect>
#include <QImage>
#include <QChar>
#include <QPainterPath>

class FontGenerator;

class EffectContext
{
public:
    EffectContext(const QChar &character, quint32 glyphIndex, const FontGenerator &generator);

    QRect bounds() const;
    const QChar& character() const;
    const FontGenerator& generator() const;
    const QPainterPath& path() const;
    const QImage& alphaMap() const;

private:
    const QChar& mCharacter;
    quint32 mGlyphIndex;
    const FontGenerator& mGenerator;
    const QImage mAlphaMap;
    QPainterPath mPath;
    QRect mBounds;
};

#endif // EFFECTCONTEXT_H
