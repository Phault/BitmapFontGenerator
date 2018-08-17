#ifndef EFFECT_H
#define EFFECT_H

#include "effectcontext.h"

#include <glyph.h>
#include <QJsonObject>

class QImage;

class Effect
{
public:
    Effect();
    Effect(const Effect &other);

    virtual ~Effect() {}
    virtual Effect *clone() const = 0;
    virtual void apply(Glyph &image, const EffectContext &context) const = 0;

    QJsonObject toJson() const;
    void fromJson(const QJsonObject &object);

    QString name() const;
    void setName(const QString &name);

    bool enabled() const;
    void setEnabled(bool enabled);

    virtual const QString &defaultName() const;
    virtual QString type() const = 0;

protected:
    virtual QJsonObject optionsToJson() const = 0;
    virtual void optionsFromJson(const QJsonObject &object) = 0;

private:
    QString mName;
    bool mEnabled;
};

#endif // EFFECT_H
