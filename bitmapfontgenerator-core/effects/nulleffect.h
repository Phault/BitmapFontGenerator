#ifndef NULLEFFECT_H
#define NULLEFFECT_H

#include "effect.h"

class NullEffect : public Effect
{
public:
    NullEffect() {}

    Effect *clone() const override
    {
        return new NullEffect();
    }

    void apply(Glyph &, const EffectContext &) const override {}

    QString type() const override
    {
        return "official.effects.null";
    }

    static NullEffect *instance()
    {
        return gInstance;
    }

protected:
    QJsonObject optionsToJson() const override { return QJsonObject(); }
    void optionsFromJson(const QJsonObject &) override {}

private:

    static NullEffect *gInstance;
};

NullEffect *NullEffect::gInstance = new NullEffect();

#endif // NULLEFFECT_H
