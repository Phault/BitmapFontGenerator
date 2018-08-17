#ifndef INNERSHADOWEFFECT_H
#define INNERSHADOWEFFECT_H

#include "shadoweffect.h"

class InnerShadowEffect : public ShadowEffect
{
public:
    InnerShadowEffect();
    InnerShadowEffect(QColor color, QPoint offset, int blurRadius);
    InnerShadowEffect(const InnerShadowEffect &other);

    void apply(Glyph &glyph, const EffectContext &) const override;

    QString type() const override;
    const QString &defaultName() const override;

    Effect *clone() const override;
};

#endif // INNERSHADOWEFFECT_H
