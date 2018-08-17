#-------------------------------------------------
#
# Project created by QtCreator 2018-07-29T22:12:17
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = bitmapfontgenerator-gui
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    fontoptions.cpp \
    characterswidget.cpp \
    pagepreview.cpp \
    sidebar.cpp \
    fonteditorwidget.cpp \
    lineargradientpreview.cpp \
    gradienteditor.cpp \
    effectseditor.cpp \
    effectstreemodel.cpp \
    textureatlaseditor.cpp

HEADERS += \
        mainwindow.h \
    fontoptions.h \
    characterswidget.h \
    pagepreview.h \
    sidebar.h \
    fonteditorwidget.h \
    lineargradientpreview.h \
    gradienteditor.h \
    effectseditor.h \
    effectstreemodel.h \
    textureatlaseditor.h

FORMS += \
        mainwindow.ui \
    fontoptions.ui \
    characterswidget.ui \
    pagepreview.ui \
    sidebar.ui \
    effectseditor.ui \
    textureatlaseditor.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../bitmapfontgenerator-core/release/ -lbitmapfontgenerator-core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../bitmapfontgenerator-core/debug/ -lbitmapfontgenerator-core
else:unix: LIBS += -L$$OUT_PWD/../bitmapfontgenerator-core/ -lbitmapfontgenerator-core

INCLUDEPATH += $$PWD/../bitmapfontgenerator-core
DEPENDPATH += $$PWD/../bitmapfontgenerator-core

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../bitmapfontgenerator-core/release/libbitmapfontgenerator-core.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../bitmapfontgenerator-core/debug/libbitmapfontgenerator-core.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../bitmapfontgenerator-core/release/bitmapfontgenerator-core.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../bitmapfontgenerator-core/debug/bitmapfontgenerator-core.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../bitmapfontgenerator-core/libbitmapfontgenerator-core.a
