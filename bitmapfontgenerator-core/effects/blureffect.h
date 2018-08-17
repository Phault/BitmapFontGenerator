#ifndef BLUREFFECT_H
#define BLUREFFECT_H

#include "effect.h"

class BlurEffect : public Effect
{
public:
    BlurEffect(int radius = 3);
    BlurEffect(const BlurEffect &other);

    Effect *clone() const override;
    void apply(Glyph &glyph, const EffectContext &) const override;

    QString type() const override;
    const QString &defaultName() const override;

    int blurRadius() const;
    void setBlurRadius(int value);

protected:
    QJsonObject optionsToJson() const override;
    void optionsFromJson(const QJsonObject &object) override;

private:
    int mBlurRadius;
};

#endif // BLUREFFECT_H
