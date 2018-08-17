#include "effectcontext.h"
#include "fontgenerator.h"

EffectContext::EffectContext(const QChar &character, quint32 glyphIndex, const FontGenerator &generator) :
    mCharacter(character),
    mGlyphIndex(glyphIndex),
    mGenerator(generator),
    mAlphaMap(generator.font().alphaMapForGlyph(glyphIndex, QRawFont::PixelAntialiasing)),
    mPath(generator.font().pathForGlyph(glyphIndex)),
    mBounds(mAlphaMap.rect())
{
    auto pathBounds = mPath.boundingRect();
    auto offset = QPointF(-pathBounds.center().x(), -pathBounds.center().y());
    mPath.translate(offset);
}

const QChar &EffectContext::character() const
{
    return mCharacter;
}

QRect EffectContext::bounds() const
{
    return mBounds;
}

const FontGenerator &EffectContext::generator() const
{
    return mGenerator;
}

const QPainterPath &EffectContext::path() const
{
    return mPath;
}

const QImage &EffectContext::alphaMap() const
{
    return mAlphaMap;
}
