#include "effectgroup.h"

#include <QJsonArray>
#include <effectfactory.h>

EffectGroup::EffectGroup() :
    mEffects()
{

}

EffectGroup::EffectGroup(const EffectGroup &other) :
    Effect(other),
    mEffects()
{
    for (const auto &effect : other.constEffects())
        mEffects.append(effect->clone());
}

EffectGroup::EffectGroup(std::initializer_list<Effect *> effects)
    : mEffects(effects)
{

}

EffectGroup::~EffectGroup()
{
    for (auto &effect : mEffects)
        delete effect;
    mEffects.clear();
}

void EffectGroup::apply(Glyph &glyph, const EffectContext &context) const
{
    for (const auto& effect : mEffects)
    {
        if (effect->enabled())
            effect->apply(glyph, context);
    }
}

QList<Effect *>& EffectGroup::effects()
{
    return mEffects;
}

const QList<Effect *> &EffectGroup::constEffects() const
{
    return mEffects;
}

QString EffectGroup::type() const
{
    return "official.effects.group";
}

QJsonObject EffectGroup::optionsToJson() const
{
    QJsonArray effectArray;

    for (const auto &effect : mEffects)
        effectArray.append(effect->toJson());

    return QJsonObject({
                           { "effects", effectArray }
                       });
}

void EffectGroup::optionsFromJson(const QJsonObject &object)
{
    auto effectArray= object["effects"].toArray();

    for (const auto effectValue : effectArray)
        mEffects.append(EffectFactory::instance()->deserialize(effectValue.toObject()));
}


Effect *EffectGroup::clone() const
{
    return new EffectGroup(*this);
}
