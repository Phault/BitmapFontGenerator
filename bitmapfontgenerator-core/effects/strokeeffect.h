#ifndef STROKEEFFECT_H
#define STROKEEFFECT_H

#include "effect.h"

class StrokeEffect : public Effect
{
public:
    StrokeEffect();
    StrokeEffect(const QColor &color, int width);
    StrokeEffect(const StrokeEffect &other);

    void apply(Glyph &glyph, const EffectContext &) const override;

    QColor color() const;
    void setColor(const QColor &color);

    int width() const;
    void setWidth(int width);

    bool adjustGlyphAdvances() const;
    void setAdjustGlyphAdvances(bool adjustGlyphAdvances);

    QString type() const override;
    const QString &defaultName() const override;

    Effect *clone() const override;

protected:
    QJsonObject optionsToJson() const override;
    void optionsFromJson(const QJsonObject &object) override;

private:
    QColor mColor { Qt::black };
    int mWidth = 5;
    bool mAdjustGlyphAdvances = false;
};

#endif // STROKEEFFECT_H
