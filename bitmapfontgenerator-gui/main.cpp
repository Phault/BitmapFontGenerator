#include "mainwindow.h"
#include <QApplication>
#include <effectfactory.h>
#include <effects/blureffect.h>
#include <effects/dropshadoweffect.h>
#include <effects/filleffect.h>
#include <effects/innershadoweffect.h>
#include <effects/strokeeffect.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto effects = EffectFactory::instance();
    effects->registerPrototype(new EffectGroup());
    effects->registerPrototype(new FillEffect());
    effects->registerPrototype(new StrokeEffect());
    effects->registerPrototype(new DropShadowEffect());
    effects->registerPrototype(new InnerShadowEffect());
    effects->registerPrototype(new BlurEffect());

    MainWindow w;
    w.show();

    return a.exec();
}
