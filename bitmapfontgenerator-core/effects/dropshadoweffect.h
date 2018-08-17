#ifndef DROPSHADOWEFFECT_H
#define DROPSHADOWEFFECT_H

#include "shadoweffect.h"


class DropShadowEffect : public ShadowEffect
{
public:
    DropShadowEffect();
    DropShadowEffect(QColor color, QPoint offset, int blurRadius);
    DropShadowEffect(const DropShadowEffect &other);

    void apply(Glyph &glyph, const EffectContext &context) const override;

    QString type() const override;
    const QString &defaultName() const override;

    Effect *clone() const override;
};

#endif // DROPSHADOWEFFECT_H
