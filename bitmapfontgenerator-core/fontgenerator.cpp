#include "fontgenerator.h"

#include <QDebug>
#include <QPainter>
#include <QChar>
#include "effects/effect.h"
#include "fontsettings.h"
#include "rectanglebinpack/maxrectsbinpack.h"
#include <utils/fontutils.h>

FontGenerator::FontGenerator(const QRawFont &font, const QString &characters) :
    mFont(font),
    mEffects(new EffectGroup()),
    mCharToGlyphIndex(),
    mGlyphIndexToChar(),
    mKerningPairs(),
    mGlyphIndexToAdvances()
{
    setCharacters(characters);
}

Glyph FontGenerator::generate(const QChar& character)
{
    // todo: check if char isn't mapped to a glyphindex
    auto glyphIndex = mCharToGlyphIndex.value(character);
    auto context = EffectContext(character, glyphIndex, *this);

    auto advances = advancesForGlyphIndex(glyphIndex);
    auto bounds = mFont.boundingRect(glyphIndex);

    Glyph glyph;
    glyph.character = character;
    glyph.xOffset = int(bounds.left()); // left bearing
    glyph.yOffset = int(bounds.top() + mFont.ascent());
    glyph.xAdvance = int(advances.x());

    const auto alphaMapSize = context.alphaMap().size();

    if (alphaMapSize.width() > 1 && alphaMapSize.height() > 1)
        glyph.image = QImage(alphaMapSize, QImage::Format_ARGB32);

    if (!glyph.image.isNull())
    {
        glyph.image.fill(Qt::transparent);
        mEffects->apply(glyph, context);

#ifdef DEBUG_GLYPH_BACKGROUND
        QPainter painter(&glyph.image);
        painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
        painter.fillRect(image.rect(), Qt::black);
#endif
    }

    return glyph;
}

BitmapFont FontGenerator::generate()
{
    QList<Glyph> glyphs;
    QList<rbp::MaxRectsBinPack> packs;

    auto margin = padding();
    auto useableWidth = pageWidth() - margin.right - margin.left;
    auto useableHeight = pageHeight() - margin.top - margin.bottom;

    for (const QChar& character : mCharacters)
    {
        Glyph glyph = generate(character);

        // most likely a whitespace character if null
        if (glyph.image.isNull())
        {
            glyph.page = 0;
            glyphs.append(glyph);
            continue;
        }

        if (glyph.image.width() > useableWidth || glyph.image.height() > useableHeight)
        {
            qWarning() << "Not enough room for glyph: " << glyph.character;
            continue;
        }

        for (int i = 0; i < packs.length(); ++i)
        {
            auto& pack = packs[i];

            auto rect = pack.Insert(glyph.image.width() + spacingHorizontal(), glyph.image.height() + spacingVertical(), mPackingMethod);
            if (rect.height != 0)
            {
                glyph.rect = QRect(rect.x, rect.y, glyph.image.width(), glyph.image.height());
                glyph.page = i;
                break;
            }
        }

        if (glyph.page == -1)
        {
            auto pack = rbp::MaxRectsBinPack(useableWidth, useableHeight, false);
            auto rect = pack.Insert(glyph.image.width() + spacingHorizontal(), glyph.image.height() + spacingVertical(), mPackingMethod);
            glyph.rect = QRect(rect.x, rect.y, glyph.image.width(), glyph.image.height());
            glyph.page = packs.length();
            packs.append(pack);
        }

        glyphs.append(std::move(glyph));
    }

    std::sort(glyphs.begin(), glyphs.end(), [](const Glyph &a, const Glyph &b) {
       return b.character > a.character;
    });

    QList<QImage> pages;

    QPainter painter;;
    for (int i = 0; i < packs.length(); i++)
    {
        QImage image(pageWidth(), pageHeight(), QImage::Format_ARGB32_Premultiplied);
        image.fill(mBackgroundColor);

        painter.begin(&image);
        for (const auto& glyph : glyphs)
        {
            if (glyph.page != i)
                continue;

            painter.drawImage(margin.left + glyph.rect.x(), margin.top + glyph.rect.y(), glyph.image);
        }
        painter.end();

        pages.append(std::move(image));
    }

    auto lineSpacing = mFont.leading() + mFont.ascent() + mFont.descent();

    BitmapFont bmFont(pages, glyphs);
    bmFont.name = mFont.familyName();
    bmFont.originalFont = mFont;
    bmFont.lineSpacing = int(lineSpacing);
    bmFont.baseLine = int(mFont.ascent());
    bmFont.kerningPairs = mKerningPairs;
    bmFont.padding = mPadding;
    bmFont.spacingHorizontal = mSpacingHorizontal;
    bmFont.spacingVertical = mSpacingVertical;
    bmFont.antiAliasing = mAntiAliasing;
    return bmFont;
}

const QRawFont &FontGenerator::font() const
{
    return mFont;
}

void FontGenerator::setFont(const QRawFont &font)
{
    mFont = font;

    updateAll();
}

QColor FontGenerator::backgroundColor() const
{
    return mBackgroundColor;
}

void FontGenerator::setBackgroundColor(const QColor &backgroundColor)
{
    mBackgroundColor = backgroundColor;
}

rbp::FreeRectChoiceHeuristic FontGenerator::packingMethod() const
{
    return mPackingMethod;
}

void FontGenerator::setPackingMethod(const rbp::FreeRectChoiceHeuristic &packingMethod)
{
    mPackingMethod = packingMethod;
}

std::shared_ptr<const EffectGroup> FontGenerator::effects() const
{
    return mEffects;
}

void FontGenerator::setEffects(std::shared_ptr<const EffectGroup> effects)
{
    mEffects = effects;
}

void FontGenerator::setEffects(std::initializer_list<Effect *> effects)
{
    mEffects = std::make_shared<EffectGroup>(effects);
}

Padding FontGenerator::padding() const
{
    return mPadding;
}

void FontGenerator::setPadding(int top, int right, int bottom, int left)
{
    mPadding.top = top;
    mPadding.right = right;
    mPadding.bottom = bottom;
    mPadding.left = left;
}

int FontGenerator::spacingHorizontal() const
{
    return mSpacingHorizontal;
}

void FontGenerator::setSpacingHorizontal(int spacingHorizontal)
{
    mSpacingHorizontal = spacingHorizontal;
}

int FontGenerator::spacingVertical() const
{
    return mSpacingVertical;
}

void FontGenerator::setSpacingVertical(int spacingVertical)
{
    mSpacingVertical = spacingVertical;
}

void FontGenerator::setSpacing(int horizontal, int vertical)
{
    mSpacingHorizontal = horizontal;
    mSpacingVertical = vertical;
}

bool FontGenerator::antiAliasing() const
{
    return mAntiAliasing;
}

void FontGenerator::setAntiAliasing(bool antiAliasing)
{
    mAntiAliasing = antiAliasing;
}

QString FontGenerator::characters() const
{
    return mCharacters;
}

void removeRepeatingCharacters(QString &chars)
{
    if (chars.isNull())
        return;

    int last = 0;

    for (int i = 1; i < chars.length(); ++i)
    {
        if (chars[i] != chars[last])
        {
            ++last;
            chars[last] = chars[i];
        }
    }

    chars.resize(++last);
}

void FontGenerator::setCharacters(const QString &characters)
{
    mCharacters = characters;
    std::sort(mCharacters.begin(), mCharacters.end());
    removeRepeatingCharacters(mCharacters);

    updateAll();
}

int FontGenerator::pageWidth() const
{
    return mPageWidth;
}

void FontGenerator::setPageWidth(int width)
{
    mPageWidth = width;
}

int FontGenerator::pageHeight() const
{
    return mPageHeight;
}

void FontGenerator::setPageHeight(int height)
{
    mPageHeight = height;
}

void FontGenerator::setPageSize(int width, int height)
{
    mPageWidth = width;
    mPageHeight = height;
}

QPointF FontGenerator::advancesForGlyphIndex(quint32 glyphIndex)
{
    auto advances = mGlyphIndexToAdvances.value(glyphIndex);

    if (advances.isNull())
    {
        QVector<quint32> glyphIndexes;
        glyphIndexes.append(glyphIndex);
        advances = mFont.advancesForGlyphIndexes(glyphIndexes, QRawFont::SeparateAdvances).at(0);
        mGlyphIndexToAdvances.insert(glyphIndex, advances);
    }

    return advances;
}

void FontGenerator::updateAll()
{
    auto glyphIndexes = mFont.glyphIndexesForString(mCharacters);
    updateGlyphIndexes(glyphIndexes);
    updateAdvances(glyphIndexes);
    updateKerningPairs(glyphIndexes);
}

void FontGenerator::updateGlyphIndexes(const QVector<quint32> &glyphIndexes)
{
    mCharToGlyphIndex.clear();
    mGlyphIndexToChar.clear();

    for (int i = 0; i < glyphIndexes.length(); i++)
    {
        mGlyphIndexToChar.insert(glyphIndexes[i], mCharacters[i]);
        mCharToGlyphIndex.insert(mCharacters[i], glyphIndexes[i]);
    }
}

void FontGenerator::updateAdvances(const QVector<quint32> &glyphIndexes)
{
    mGlyphIndexToAdvances.clear();

    auto advances = mFont.advancesForGlyphIndexes(glyphIndexes, QRawFont::SeparateAdvances);

    for (int i = 0; i < advances.length(); ++i)
        mGlyphIndexToAdvances.insert(glyphIndexes[i], advances[i]);
}

void FontGenerator::updateKerningPairs(const QVector<quint32> &glyphIndexes)
{
    mKerningPairs.clear();

    QSet<quint32> glyphIndexSet;
    for (const auto& glyphIndex : glyphIndexes)
        glyphIndexSet.insert(glyphIndex);

    mKerningPairs.clear();
    auto fullKernelPairs = FontUtils::getKerningPairs(mFont, glyphIndexSet);

    for (auto iterator = fullKernelPairs.constBegin(); iterator != fullKernelPairs.constEnd(); ++iterator)
    {
        const auto &pair = iterator.key();

        auto left = mGlyphIndexToChar.value(quint32(pair.first));
        auto right = mGlyphIndexToChar.value(quint32(pair.second));

        QPair<QChar, QChar> charPair(left, right);
        mKerningPairs.insert(charPair, iterator.value());
    }
}
