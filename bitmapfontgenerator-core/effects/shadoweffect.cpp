#include "shadoweffect.h"

ShadowEffect::ShadowEffect()
{

}

ShadowEffect::ShadowEffect(const ShadowEffect &other) :
    Effect(other),
    color(other.color),
    offset(other.offset),
    blurRadius(other.blurRadius)
{

}

QJsonObject ShadowEffect::optionsToJson() const
{
    QJsonObject object({
                           { "blurRadius", blurRadius },
                           { "color", color.name(QColor::HexArgb) }
                       });

    if (!offset.isNull())
    {
        object["offset"] = QJsonObject({
                                           {"x", offset.x() },
                                           {"y", offset.y() }
                                       });
    }

    return object;
}

void ShadowEffect::optionsFromJson(const QJsonObject &object)
{
    blurRadius = object["blurRadius"].toInt(blurRadius);

    if (object.contains("color"))
        color.setNamedColor(object["color"].toString());

    auto offsetJson = object["offset"].toObject();
    if (!offsetJson.isEmpty())
    {
        offset.setX(offsetJson["x"].toInt());
        offset.setY(offsetJson["y"].toInt());
    }
}
