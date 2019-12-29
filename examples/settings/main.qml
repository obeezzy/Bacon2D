import QtQuick 2.13
import Bacon2D 1.0
import QtQuick.Controls 2.13

Game {
    id: game
    width: 800
    height: 600
    currentScene: scene
    gameName: "some.example.game"
    deviceScreen {
        requestedOrientation: Qt.LandscapeOrientation
        alwaysOn: true
    }

    Settings {
        id: settings
        property int highScore: 0
        property bool noSound: false
    }

    Scene {
        id: scene
        anchors.fill: parent
        scale: game.isMobile ? game.deviceScreen.availableHeight / game.height : 1
        transformOrigin: Item.TopLeft

        Column {
            anchors.fill: parent
            Text {
                id: disp
                text: settings.highScore
            }

            SpinBox {
                width: 200
                value: settings.highScore
                onValueChanged: settings.highScore = value
            }
        }
    }
}
