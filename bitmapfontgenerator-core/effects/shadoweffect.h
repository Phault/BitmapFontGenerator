#ifndef SHADOWEFFECT_H
#define SHADOWEFFECT_H

#include "effect.h"

#include <QColor>

class ShadowEffect : public Effect
{
public:
    ShadowEffect();
    ShadowEffect(const ShadowEffect &other);

    QColor color { Qt::black };
    QPoint offset { 0, 0 };
    int blurRadius = 5;

protected:
    QJsonObject optionsToJson() const override;
    void optionsFromJson(const QJsonObject &object) override;
};

#endif // SHADOWEFFECT_H
