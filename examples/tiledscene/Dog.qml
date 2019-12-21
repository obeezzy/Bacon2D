import QtQuick 2.13
import Bacon2D 1.0
import "dog"

PhysicsEntity {
    id: dog
    entityType: "dog"

    readonly property int groundSensorRoom: -7
    readonly property int xStep: 10
    readonly property ActionController controls: actionController
    property bool airborne: false

    sleepingAllowed: false
    width: 80
    height: 64
    bodyType: Body.Dynamic
    fixedRotation: true

    Keys.enabled: dog.game ? dog.game.gameState !== Bacon2D.Paused : true
    Keys.forwardTo: actionController

    fixtures: [
        Box {
            x: 15
            width: target.width - 40
            height: target.height - groundSensorRoom
            density: .01
            restitution: 0
            friction: .01
            categories: Box.Category1
        },

        // ground sensor
        Box {
            sensor: true
            x: target.width / 2 - width / 2
            y: target.height - groundSensorRoom
            width: 30
            height: 2

            onBeginContact: dog.airborne = false;
            onEndContact: dog.airborne = true;
        }
    ]

    ActionController { id: actionController }

    StateController {
        id: stateController
        anchors.fill: parent
        actor: dog
    }
}

