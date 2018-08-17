#ifndef EFFECTFACTORY_H
#define EFFECTFACTORY_H

#include <effects/effect.h>

class EffectFactory
{
public:
    static EffectFactory *instance();

    void registerPrototype(const Effect *prototype);
    bool unregisterPrototype(const Effect *prototype);
    bool unregisterPrototype(const QString &id);
    bool isRegistered(const QString &id) const;

    const Effect *prototype(const QString &id) const;

    Effect *create(const QString &id) const;

//    template <typename T>
//    T *create(const QString &id) const;

    Effect *deserialize(const QJsonObject effectJson) const;

//    template <typename T>
//    T *deserialize(const QJsonDocument effectJson) const;

private:
    EffectFactory();

    static EffectFactory *gInstance;
    QHash<const QString, const Effect *> mPrototypes;
};

#endif // EFFECTFACTORY_H
