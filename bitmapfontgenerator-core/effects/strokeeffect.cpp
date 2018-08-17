#include "strokeeffect.h"
#include "../imageprocessing/imageeffects.h"


StrokeEffect::StrokeEffect()
{

}

StrokeEffect::StrokeEffect(const QColor &color, int width) :
    mColor(color),
    mWidth(width)
{

}

StrokeEffect::StrokeEffect(const StrokeEffect &other) :
    Effect (other),
    mColor(other.mColor),
    mWidth(other.mWidth),
    mAdjustGlyphAdvances(other.mAdjustGlyphAdvances)
{

}

void StrokeEffect::apply(Glyph &glyph, const EffectContext &) const
{
    glyph.image = ImageEffects::applyOutline(glyph.image, mColor, mWidth);
    glyph.xOffset -= mWidth;
    glyph.yOffset -= mWidth;

    if (adjustGlyphAdvances())
        glyph.xAdvance += mWidth;
}

QColor StrokeEffect::color() const
{
    return mColor;
}

void StrokeEffect::setColor(const QColor &color)
{
    mColor = color;
}

int StrokeEffect::width() const
{
    return mWidth;
}

void StrokeEffect::setWidth(int width)
{
    mWidth = width;
}

bool StrokeEffect::adjustGlyphAdvances() const
{
    return mAdjustGlyphAdvances;
}

void StrokeEffect::setAdjustGlyphAdvances(bool adjustGlyphAdvances)
{
    mAdjustGlyphAdvances = adjustGlyphAdvances;
}

QString StrokeEffect::type() const
{
    return "official.effects.stroke";
}


QJsonObject StrokeEffect::optionsToJson() const
{
    return QJsonObject({
                           { "color", mColor.name(QColor::HexArgb) },
                           { "width", mWidth },
                           { "adjustGlyphAdvances", mAdjustGlyphAdvances }
                       });
}

void StrokeEffect::optionsFromJson(const QJsonObject &object)
{
    if (object.contains("color"))
        mColor.setNamedColor(object["color"].toString());
    mWidth = object["width"].toInt(mWidth);
    mAdjustGlyphAdvances = object["adjustGlyphAdvances"].toBool(mAdjustGlyphAdvances);
}


const QString &StrokeEffect::defaultName() const
{
    static QString defaultName = "Stroke";
    return defaultName;
}

Effect *StrokeEffect::clone() const
{
    return new StrokeEffect(*this);
}
