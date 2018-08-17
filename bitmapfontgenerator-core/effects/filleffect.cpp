#include "filleffect.h"

#include <QGlyphRun>
#include <QJsonArray>
#include <QPainter>

FillEffect::FillEffect()
{

}

FillEffect::FillEffect(const QBrush &brush) :
    mBrush(brush)
{

}

FillEffect::FillEffect(const FillEffect &other) :
    Effect(other),
    mBrush(other.mBrush)
{

}

void FillEffect::apply(Glyph &glyph, const EffectContext &context) const
{
    auto fill = context.alphaMap().convertToFormat(QImage::Format_ARGB32_Premultiplied);

    QPainter painter(&fill);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(fill.rect(), mBrush);
    painter.end();

    auto deltaSize = glyph.image.size() - fill.size();

    painter.begin(&glyph.image);
    painter.drawImage(deltaSize.width() / 2, deltaSize.height() / 2, fill);
}

QBrush FillEffect::brush() const
{
    return mBrush;
}

void FillEffect::setBrush(const QBrush &brush)
{
    mBrush = brush;
}

QString FillEffect::type() const
{
    return "official.effects.fill";
}

QJsonObject FillEffect::optionsToJson() const
{
    return QJsonObject({
                           { "brush", brushToJson(mBrush) }
                       });
}

void FillEffect::optionsFromJson(const QJsonObject &object)
{
    mBrush = brushFromJson(object["brush"].toObject());
}

QJsonObject FillEffect::brushToJson(const QBrush &brush) const
{
    QJsonObject object;

    auto gradient = mBrush.gradient();
    if (gradient)
        object["gradient"] = gradientToJson(*gradient);
    else
    {
        object["style"] = int(brush.style());
        object["color"] = brush.color().name(QColor::HexArgb);
    }

    return object;
}

QBrush FillEffect::brushFromJson(const QJsonObject &object) const
{
    // todo: support patterns and transformation

    if (object.contains("gradient"))
    {
        return gradientFromJson(object["gradient"].toObject());
    }
    else
    {
        auto style = Qt::BrushStyle(object["style"].toInt());
        auto color = QColor(object["color"].toString());

        return QBrush(color, style);
    }
}

QJsonObject FillEffect::gradientToJson(const QGradient &gradient) const
{
    QJsonObject object({
                           { "type", gradient.type() },
                           { "spread", gradient.spread() },
                           { "coordinateMode", gradient.coordinateMode() }
                       });

    QJsonArray stopVariants;
    for (const auto &stop : gradient.stops())
    {
        QJsonObject stopVariant({
                                    { "position", stop.first },
                                    { "color", stop.second.name(QColor::HexArgb) }
                                });
        stopVariants.append(stopVariant);
    }
    object["stops"] = stopVariants;
    return object;
}

QGradient FillEffect::gradientFromJson(const QJsonObject &object) const
{
    auto type = QGradient::Type(object["type"].toInt());

    QGradient gradient;
    switch (type) {
        case QGradient::ConicalGradient:
            gradient = QConicalGradient();
            break;
        case QGradient::LinearGradient:
            gradient = QLinearGradient();
            break;
        case QGradient::RadialGradient:
            gradient = QRadialGradient();
            break;
        default:
            return gradient;
    }

    gradient.setSpread(QGradient::Spread(object.value("spread").toInt()));
    gradient.setCoordinateMode(QGradient::CoordinateMode(object.value("coordinateMode").toInt()));

    auto stopVariants = object["stops"].toArray();
    QGradientStops stops;

    for (const auto stop : stopVariants)
    {
        const auto stopMap = stop.toObject();
        auto position = stopMap["position"].toDouble();
        auto color = QColor(stopMap["color"].toString());

        stops.append({ position, color });
    }

    gradient.setStops(stops);

    return gradient;
}

const QString &FillEffect::defaultName() const
{
    static QString defaultName = "Fill";
    return defaultName;
}

Effect *FillEffect::clone() const
{
    return new FillEffect(*this);
}
