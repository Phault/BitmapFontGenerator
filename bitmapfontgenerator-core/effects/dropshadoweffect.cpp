#include "dropshadoweffect.h"
#include "../imageprocessing/imageeffects.h"

DropShadowEffect::DropShadowEffect()
{

}

DropShadowEffect::DropShadowEffect(QColor color, QPoint offset, int blurRadius)
{
    this->color = color;
    this->offset = offset;
    this->blurRadius = blurRadius;
}

DropShadowEffect::DropShadowEffect(const DropShadowEffect &other) :
    ShadowEffect (other)
{

}

void DropShadowEffect::apply(Glyph &glyph, const EffectContext &/*context*/) const
{
    glyph.image = ImageEffects::applyDropShadow(glyph.image,
                                          color,
                                          blurRadius,
                                          offset);
}

QString DropShadowEffect::type() const
{
    return "official.effects.dropshadow";
}


const QString &DropShadowEffect::defaultName() const
{
    static QString defaultName = "Drop Shadow";
    return defaultName;
}


Effect *DropShadowEffect::clone() const
{
    return new DropShadowEffect(*this);
}
