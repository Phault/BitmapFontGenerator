#ifndef FILLEFFECT_H
#define FILLEFFECT_H

#include "effect.h"

#include <QBrush>

class FillEffect : public Effect
{
public:
    FillEffect();
    FillEffect(const QBrush &brush);
    FillEffect(const FillEffect &other);

    void apply(Glyph &glyph, const EffectContext &context) const override;

    QBrush brush() const;
    void setBrush(const QBrush &brush);

    QString type() const override;
    const QString &defaultName() const override;

    Effect *clone() const override;

protected:
    QJsonObject optionsToJson() const override;
    void optionsFromJson(const QJsonObject &object) override;

private:
    QJsonObject brushToJson(const QBrush &brush) const;
    QBrush brushFromJson(const QJsonObject &object) const;

    QJsonObject gradientToJson(const QGradient &gradient) const;
    QGradient gradientFromJson(const QJsonObject &object) const;

    QBrush mBrush;
};

#endif // FILLEFFECT_H
