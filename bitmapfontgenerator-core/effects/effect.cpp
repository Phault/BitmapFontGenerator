#include "effect.h"

#include <QIcon>

Effect::Effect() :
    mName("Effect"),
    mEnabled(true)
{

}

Effect::Effect(const Effect &other) :
    mName(other.mName),
    mEnabled(other.mEnabled)
{

}

QJsonObject Effect::toJson() const
{
    return QJsonObject({
                           { "type", type() },
                           { "name", mName },
                           { "enabled", mEnabled },
                           { "options", optionsToJson() }
                       });
}

void Effect::fromJson(const QJsonObject &object)
{
    mName = object["name"].toString(defaultName());
    mEnabled = object["enabled"].toBool(true);
    optionsFromJson(object["options"].toObject());
}

QString Effect::name() const
{
    return mName;
}

void Effect::setName(const QString &name)
{
    mName = name;
}

bool Effect::enabled() const
{
    return mEnabled;
}

void Effect::setEnabled(bool enabled)
{
    mEnabled = enabled;
}

const QString &Effect::defaultName() const
{
    static QString defaultName = "Effect";
    return defaultName;
}
