#include "effectfactory.h"

#include <QJsonObject>
#include <exception>

EffectFactory *EffectFactory::gInstance = nullptr;

EffectFactory::EffectFactory() :
    mPrototypes()
{

}

EffectFactory *EffectFactory::instance()
{
    if (gInstance == nullptr)
        gInstance = new EffectFactory();

    return gInstance;
}

void EffectFactory::registerPrototype(const Effect *prototype)
{
    auto type = prototype->type();

    if (isRegistered(type))
        throw std::invalid_argument(QString("prototype is already registered: '%1'").arg(type).toStdString());

    mPrototypes.insert(type, prototype);
}

bool EffectFactory::unregisterPrototype(const Effect *prototype)
{
    return unregisterPrototype(prototype->type());
}

bool EffectFactory::unregisterPrototype(const QString &id)
{
    return mPrototypes.remove(id) != 0;
}

bool EffectFactory::isRegistered(const QString &id) const
{
    return mPrototypes.contains(id);
}

Effect *EffectFactory::create(const QString &id) const
{
    if (!isRegistered(id))
        return nullptr;

    return mPrototypes.value(id)->clone();
}

Effect *EffectFactory::deserialize(const QJsonObject effectJson) const
{
    auto type = effectJson.value("type").toString();

    if (type.isNull())
        throw std::invalid_argument("json object has no 'type' key");

    auto effect = create(type);
    effect->fromJson(effectJson);
    return effect;
}
