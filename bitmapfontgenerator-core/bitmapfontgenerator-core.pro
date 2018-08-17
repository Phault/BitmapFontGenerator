#-------------------------------------------------
#
# Project created by QtCreator 2018-07-09T12:28:39
#
#-------------------------------------------------

QT += gui

TARGET = bitmapfontgenerator-core
TEMPLATE = lib
CONFIG += staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    effects/blureffect.cpp \
    effects/dropshadoweffect.cpp \
    effects/effectgroup.cpp \
    effects/filleffect.cpp \
    imageprocessing\imageeffects.cpp \
    imageprocessing\fastgaussianblur.cpp \
    effects/innershadoweffect.cpp \
    effects/strokeeffect.cpp \
    fontgenerator.cpp \
    bitmapfont.cpp \
    rectanglebinpack/maxrectsbinpack.cpp \
    rectanglebinpack/rect.cpp \
    utils/fontutils.cpp \
    effects/effectcontext.cpp \
    exporters/angelcode/angelcodetextexporter.cpp \
    exporters/angelcode/angelcodebinaryexporter.cpp \
    exporters/angelcode/angelcodexmlexporter.cpp \
    exporters/angelcode/angelcodejsonexporter.cpp \
    exporters/angelcode/angelcodefont.cpp \
    exporters/exporter.cpp \
    effects/effect.cpp \
    effects/shadoweffect.cpp \
    effectfactory.cpp

HEADERS += \
    effects/blureffect.h \
    effects/dropshadoweffect.h \
    effects/effect.h \
    effects/effectcontext.h \
    effects/effectgroup.h \
    effects/filleffect.h \
    imageprocessing\imageeffects.h \
    imageprocessing\fastgaussianblur.h \
    effects/innershadoweffect.h \
    effects/shadoweffect.h \
    effects/strokeeffect.h \
    fontgenerator.h \
    glyph.h \
    padding.h \
    bitmapfont.h \
    rectanglebinpack/maxrectsbinpack.h \
    rectanglebinpack/rect.h \
    utils/fontutils.h \
    exporters/angelcode/angelcodetextexporter.h \
    exporters/angelcode/angelcodebinaryexporter.h \
    exporters/angelcode/infoblock.h \
    exporters/angelcode/blocktype.h \
    exporters/angelcode/commonblock.h \
    exporters/angelcode/pagesblock.h \
    exporters/angelcode/charsblock.h \
    exporters/angelcode/kerningblock.h \
    exporters/angelcode/angelcodexmlexporter.h \
    exporters/angelcode/angelcodejsonexporter.h \
    exporters/angelcode/angelcodefont.h \
    exporters/exporter.h \
    effectfactory.h \
    effects/nulleffect.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
