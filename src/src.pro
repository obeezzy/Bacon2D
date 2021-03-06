TEMPLATE = lib
CONFIG += qt plugin

QMAKE_HOST_ARCH=$$QMAKE_HOST.arch
  !equals(QMAKE_HOST_ARCH, $$QT_ARCH) {
     CONFIG += cross_build
}

CONFIG += c++17

QT += quick
android: QT += androidextras

TARGET = bacon2dplugin
TARGETPATH = Bacon2D
API_VER=1.0

DESTDIR = $$OUT_PWD/qml/Bacon2D

OBJECTS_DIR = tmp
MOC_DIR = tmp

DEPENDPATH += .
INCLUDEPATH += . \
    ./private \
    ../3rdparty/qml-box2d \
    ../3rdparty/tiled/src

DEFINES += STATIC_PLUGIN_BOX2D
win32:DEFINES += WIN32

include(../3rdparty/qml-box2d/box2d-static.pri)
include(../3rdparty/tiled/src/libtiled/libtiled-static.pri)
include($$PWD/tmx/tmx.pri)

HEADERS += \
    buttonpadkeynavigation.h \
    enums.h \
    gesturepadkeynavigation.h \
    keyaction.h \
    keyinput.h \
    scene.h \
    game.h \
    private/plugins.h \
    private/spritesheet.h \
    spriteanimation.h \
    private/animationtransition.h \
    private/animationchangeevent.h \
    tiledimage.h \
    tiledmap.h \
    viewport.h \
    scriptbehavior.h \
    scrollbehavior.h \
    scrollbehaviorimpl.h \
    imagelayerscrollbehavior.h \
    layerscrollbehavior.h \
    settings.h \
    tiledlayer.h \
    tiledscene.h \
    sprite.h \
    physicsentity.h \
    pausabletimer.h \
    spritestrip.h \
    spritesheetgrid.h \
    tiledpropertymapping.h \
    animatedsprite.h \
    behavior.h \
    entity.h \
    entitymanager.h \
    bacon2dimagelayer.h \
    bacon2dlayer.h \
    private/entityfactory.h \
    tiledobjectgroup.h \
    private/keyeventforwarder.h \
    virtualjoystickkeynavigation.h \
    private/keynavigation.h

SOURCES += \
    buttonpadkeynavigation.cpp \
    enums.cpp \
    gesturepadkeynavigation.cpp \
    keyaction.cpp \
    keyinput.cpp \
    scene.cpp \
    game.cpp \
    private/plugins.cpp \
    private/spritesheet.cpp \
    spriteanimation.cpp \
    private/animationtransition.cpp \
    tiledimage.cpp \
    tiledmap.cpp \
    viewport.cpp \
    scriptbehavior.cpp \
    scrollbehavior.cpp \
    imagelayerscrollbehavior.cpp \
    layerscrollbehavior.cpp \
    settings.cpp \
    tiledscene.cpp \
    tiledlayer.cpp \
    sprite.cpp \
    physicsentity.cpp \
    pausabletimer.cpp \
    spritestrip.cpp \
    spritesheetgrid.cpp \
    tiledpropertymapping.cpp \
    animatedsprite.cpp \
    behavior.cpp \
    entity.cpp \
    entitymanager.cpp \
    bacon2dimagelayer.cpp \
    bacon2dlayer.cpp \
    private/entityfactory.cpp \
    tiledobjectgroup.cpp \
    private/keyeventforwarder.cpp \
    virtualjoystickkeynavigation.cpp \
    private/keynavigation.cpp

QMLFILES += \
            $$PWD/InfiniteScrollEntity.qml \
            $$PWD/BoxBody.qml \
            $$PWD/ChainBody.qml \
            $$PWD/CircleBody.qml \
            $$PWD/EdgeBody.qml \
            $$PWD/ImageBoxBody.qml \
            $$PWD/PolygonBody.qml \
            $$PWD/Boundaries.qml \
            $$PWD/RectangleBoxBody.qml \
            $$PWD/VirtualJoystick.qml \
            $$PWD/GesturePad.qml \
            $$PWD/ButtonPad.qml \
            $$PWD/qmldir

# Copy qml files post build
win32 {
    DESTDIR ~= s,/,\\,g
    QMLFILES ~= s,/,\\,g
    for(FILE, QMLFILES){
        QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$FILE) $$quote($$DESTDIR) $$escape_expand(\\n\\t)
    }
    QMAKE_POST_LINK += $$[QT_INSTALL_BINS]/qmlplugindump -noinstantiate -notrelocatable Bacon2D $$API_VER $$OUT_PWD/qml > $$DESTDIR\plugins.qmltypes
}
unix {
    QMAKE_POST_LINK += $$QMAKE_COPY $$QMLFILES $$DESTDIR $$escape_expand(\\n\\t)
    !cross_build {
        QMAKE_POST_LINK += $$[QT_INSTALL_BINS]/qmlplugindump -noinstantiate -notrelocatable Bacon2D $$API_VER $$OUT_PWD/qml > $$DESTDIR/plugins.qmltypes
    }
}

target.path = $$[QT_INSTALL_QML]/$$replace(TARGETPATH, \\., /).$$API_VER

qmltypes.path = $${target.path}
qmltypes.files += $$DESTDIR/plugins.qmltypes
export(qmltypes.files)

QMAKE_EXTRA_TARGETS += qmltypes

!android {
    qmlpluginfiles.path = $${target.path}
    qmlpluginfiles.files = $$QMLFILES
    QMAKE_EXTRA_TARGETS += qmlpluginfiles
    INSTALLS += qmlpluginfiles
} else: android {
    QMAKE_POST_LINK += rm -rf $${target.path} && $$QMAKE_COPY_DIR $$OUT_PWD/qml/Bacon2D $${target.path}
}

INSTALLS += target qmltypes

DISTFILES += \
    ButtonPad.qml
