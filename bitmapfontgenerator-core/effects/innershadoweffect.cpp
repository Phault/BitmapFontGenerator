#include "innershadoweffect.h"
#include "../imageprocessing/imageeffects.h"


InnerShadowEffect::InnerShadowEffect()
{

}

InnerShadowEffect::InnerShadowEffect(QColor color, QPoint offset, int blurRadius)
{
    this->color = color;
    this->offset = offset;
    this->blurRadius = blurRadius;
}

InnerShadowEffect::InnerShadowEffect(const InnerShadowEffect &other) :
    ShadowEffect (other)
{

}

void InnerShadowEffect::apply(Glyph &glyph, const EffectContext &) const
{
    glyph.image = ImageEffects::applyInnerShadow(glyph.image,
                                          color,
                                          blurRadius,
                                          offset);
}

QString InnerShadowEffect::type() const
{
    return "official.effects.innershadow";
}

const QString &InnerShadowEffect::defaultName() const
{
    static QString defaultName = "Inner Shadow";
    return defaultName;
}

Effect *InnerShadowEffect::clone() const
{
    return new InnerShadowEffect(*this);
}
