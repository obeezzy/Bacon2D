import QtQuick 2.13
import Bacon2D 1.0

Game {
    id: game
    title: qsTr("Bacon2D - Spritesheet")
    width: 640
    height: 640
    currentScene: scene
    deviceScreen {
        requestedOrientation: Qt.LandscapeOrientation
        alwaysOn: true
    }

    Scene {
        id: scene

        width: parent.width
        height: parent.height
        focus: true
        scale: game.isMobile ? game.deviceScreen.availableHeight / game.height : 1
        transformOrigin: Item.Top

        property int currentIndex: 0

        GesturePad {
            anchors.fill: parent
            keyNavigation: GesturePadKeyNavigation {
                swipeLeft: Qt.Key_Right
                swipeRight: Qt.Key_Left
                doubleTap: Qt.Key_Space
            }
        }

        Keys.onPressed: {
            switch(event.key) {
            case Qt.Key_Left:
                if (currentIndex > 0) {
                    --currentIndex;
                    sprite.animation = sprite.animations[currentIndex].name;
                }
                break;
            case Qt.Key_Right:
                if (currentIndex < sprite.spriteSheet.verticalFrameCount - 1) {
                    ++currentIndex;
                    sprite.animation = sprite.animations[currentIndex].name;
                }
                break;
            case Qt.Key_Space:
                sprite.horizontalMirror = !sprite.horizontalMirror;
                break;
            }
        }

        Text {
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 40
            color: "crimson"
            text: sprite.animation
        }

        AnimatedSprite {
            id: sprite
            anchors.centerIn: parent
            animation: "run"
            spriteSheet: SpriteSheet {
                id: spriteSheet
                source: "images/sprite.png"
                horizontalFrameCount: 10
                verticalFrameCount: 3
            }

            animations: [
                SpriteAnimation {
                    name: "idle"
                    duration: 500
                    loops: Animation.Infinite
                },

                SpriteAnimation {
                    name: "run"
                    duration: 500
                    loops: Animation.Infinite
                    spriteStrip: SpriteStrip {
                        finalFrame: 7
                        frameY: 2 * frameHeight
                    }
                },

                SpriteAnimation {
                    name: "jump"
                    duration: 1000
                    loops: Animation.Infinite
                    spriteStrip: SpriteStrip {
                        frameY: frameHeight
                        finalFrame: 7
                    }
                }
            ]
        }
    }
}
