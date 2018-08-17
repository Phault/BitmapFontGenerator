#ifndef EFFECTGROUP_H
#define EFFECTGROUP_H

#include <QList>
#include "effect.h"



class EffectGroup : public Effect
{
public:
    EffectGroup();
    EffectGroup(const EffectGroup &other);
    EffectGroup(std::initializer_list<Effect *> mEffects);
    ~EffectGroup() override;

    Effect *clone() const override;
    void apply(Glyph &glyph, const EffectContext &context) const override;

    QList<Effect *>& effects();
    const QList<Effect *>& constEffects() const;

    QString type() const override;

protected:
    QJsonObject optionsToJson() const override;
    void optionsFromJson(const QJsonObject &object) override;

private:
    QList<Effect *> mEffects;    
};

#endif // EFFECTGROUP_H
