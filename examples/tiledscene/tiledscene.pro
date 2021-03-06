EXAMPLE_QML_FILES += \
    Coin.qml \
    Actor.qml \
    Ground.qml \
    LevelBoundaries.qml \
    Polyground.qml \
    actor/ActionController.qml \
    actor/StateController.qml \
    ActorButtonPad.qml

EXAMPLE_IMAGE_FILES += \
    images/coin.png \
    images/coin_icon.png \
    images/sprite.png \
    images/player.png \
    levels/background.png \
    levels/winter_tileset.png

EXAMPLE_TMX_FILES += \
    levels/example.tmx

include(../shared/example.pri)
