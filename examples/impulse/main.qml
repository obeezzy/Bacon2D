import QtQuick 2.13
import Bacon2D 1.0

Game {
    id: game
    width: 800
    height: 600
    currentScene: scene
    deviceScreen {
        requestedOrientation: Qt.LandscapeOrientation
        alwaysOn: true
    }

    Scene {
        id: scene
        width: game.width
        height: game.height
        physics: true
        debug: true
        scale: game.isMobile ? game.deviceScreen.availableHeight / game.height : 1
        transformOrigin: Item.Top

        Boundaries {}

        Ball {
            id: ball
            x: parent.x
            y: parent.y
            rotation: 0
            width: 50
            height: 50
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                ball.body.applyLinearImpulse(
                            Qt.point((mouseX - ball.x),
                                     (mouseY - ball.y)),
                            Qt.point(ball.x, ball.y))
            }
        }
        Item {
            id: innerBox
            anchors.centerIn: scene
            width: 300
            height: 300

            Boundaries {
                anchors.fill: parent
                Rectangle {
                    anchors.fill: parent
                    color: "black"
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    innerBall.body.applyLinearImpulse(
                                Qt.point((mouseX - innerBall.x),
                                         (mouseY - innerBall.y)),
                                Qt.point(innerBall.x, innerBall.y))
                }
            }
        }

        Ball {
            id: innerBall

            x: innerBox.x + innerBox.width/2
            y: innerBox.y + innerBox.height/2
            rotation: 0
            width: 50
            height: 50
        }


    }

    Rectangle {
        id: debugButton
        anchors {
            left: parent.left
            top: parent.top
        }
        z: 10
        width: 120
        height: 30
        Text {
            id: debugButtonText
            text: scene.debug ? "Debug view: on" : "Debug view: off"
            anchors.centerIn: parent
        }
        color: "#DEDEDE"
        border.color: "#999"
        radius: 5
        MouseArea {
            anchors.fill: parent
            onClicked: scene.debug = !scene.debug
        }
    }
}
