#include "blureffect.h"
#include "../imageprocessing/fastgaussianblur.h"


BlurEffect::BlurEffect(int radius) :
    mBlurRadius(radius)
{

}

BlurEffect::BlurEffect(const BlurEffect &other) :
    Effect(other),
    mBlurRadius(other.mBlurRadius)
{

}

void BlurEffect::apply(Glyph &glyph, const EffectContext &) const
{
    auto resizedImage = glyph.image.copy(-mBlurRadius,
                                         -mBlurRadius,
                                         glyph.image.width() + mBlurRadius * 2,
                                         glyph.image.height() + mBlurRadius * 2);
    glyph.image = FastGaussianBlur::applyBlur(resizedImage, mBlurRadius);

    glyph.xOffset -= mBlurRadius;
    glyph.yOffset -= mBlurRadius;
}

int BlurEffect::blurRadius() const
{
    return mBlurRadius;
}

void BlurEffect::setBlurRadius(int value)
{
    mBlurRadius = value;
}

QJsonObject BlurEffect::optionsToJson() const
{
    return QJsonObject({
                        { "blurRadius", mBlurRadius }
                    });
}

void BlurEffect::optionsFromJson(const QJsonObject &object)
{
    mBlurRadius = object["blurRadius"].toInt(mBlurRadius);
}

QString BlurEffect::type() const
{
    return "official.effects.blur";
}

Effect *BlurEffect::clone() const
{
    return new BlurEffect(*this);
}

const QString &BlurEffect::defaultName() const
{
    static QString defaultName = "Blur";
    return defaultName;
}
