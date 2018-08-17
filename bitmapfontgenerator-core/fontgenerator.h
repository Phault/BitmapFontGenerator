#ifndef FONTGENERATOR_H
#define FONTGENERATOR_H

#include <QList>
#include <effects/effectgroup.h>
#include "bitmapfont.h"
#include "glyph.h"
#include "padding.h"
#include "rectanglebinpack/maxrectsbinpack.h"

struct FontSettings;
class Effect;
class QChar;

class FontGenerator
{
public:
    FontGenerator() = default;
    FontGenerator(const QRawFont &font, const QString &characters);

    Glyph generate(const QChar& character);
    BitmapFont generate();

    const QRawFont &font() const;
    void setFont(const QRawFont &font);

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &backgroundColor);

    rbp::FreeRectChoiceHeuristic packingMethod() const;
    void setPackingMethod(const rbp::FreeRectChoiceHeuristic &packingMethod);

    std::shared_ptr<const EffectGroup> effects() const;
    void setEffects(std::shared_ptr<const EffectGroup> effects);
    void setEffects(std::initializer_list<Effect*> effects);

    Padding padding() const;
    void setPadding(const Padding &padding);
    void setPadding(int top, int right, int bottom, int left);

    int spacingHorizontal() const;
    void setSpacingHorizontal(int spacingHorizontal);

    int spacingVertical() const;
    void setSpacingVertical(int spacingVertical);

    void setSpacing(int horizontal, int vertical);

    bool antiAliasing() const;
    void setAntiAliasing(bool antiAliasing);

    QString characters() const;
    void setCharacters(const QString &characters);

    int pageWidth() const;
    void setPageWidth(int width);

    int pageHeight() const;
    void setPageHeight(int height);

    void setPageSize(int width, int height);

private:
    QPointF advancesForGlyphIndex(quint32 glyphIndex);
    void updateAll();
    void updateGlyphIndexes(const QVector<quint32> &glyphIndexes);
    void updateAdvances(const QVector<quint32> &glyphIndexes);
    void updateKerningPairs(const QVector<quint32> &glyphIndexes);

    QRawFont mFont;
    QColor mBackgroundColor = Qt::transparent;
    rbp::FreeRectChoiceHeuristic mPackingMethod = rbp::FreeRectChoiceHeuristic::BestShortSideFit;
    std::shared_ptr<const EffectGroup> mEffects;
    Padding mPadding { 0, 0, 0, 0};
    int mSpacingHorizontal = 1;
    int mSpacingVertical = 1;
    bool mAntiAliasing = true;
    QString mCharacters = "";
    int mPageWidth = 256;
    int mPageHeight = 256;

    // todo: there must be a better way than having two maps
    QHash<QChar, quint32> mCharToGlyphIndex;
    QHash<quint32, QChar> mGlyphIndexToChar;

    QMap<QPair<QChar, QChar>, qreal> mKerningPairs;
    QHash<quint32, QPointF> mGlyphIndexToAdvances;
};

#endif // FONTGENERATOR_H
