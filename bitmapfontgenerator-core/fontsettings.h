#ifndef FONTSETTINGS_H
#define FONTSETTINGS_H

#include "rectanglebinpack/maxrectsbinpack.h"
#include "padding.h"

#include <QColor>
#include <QList>
#include <QRawFont>

class Effect;

struct FontSettings
{
    QRawFont font;
    bool antialiasing = true;
    Padding glyphPadding;
    QColor backgroundColor = Qt::transparent;
    rbp::FreeRectChoiceHeuristic packingMethod { rbp::FreeRectChoiceHeuristic::BestShortSideFit };
    QList<Effect *> effects;
};

#endif // FONTSETTINGS_H
