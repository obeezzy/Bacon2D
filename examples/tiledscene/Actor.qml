import QtQuick 2.13
import Bacon2D 1.0
import "actor"

PhysicsEntity {
    id: actor
    entityType: "actor"

    readonly property int groundSensorRoom: -7
    readonly property int xStep: 10
    readonly property ActionController controls: actionController
    property bool airborne: false

    sleepingAllowed: false
    width: 80
    height: 64
    bodyType: Body.Dynamic
    fixedRotation: true

    Keys.enabled: actor.game ? actor.game.gameState !== Bacon2D.Paused : true
    Keys.forwardTo: actionController
    viewportTracker {
        enabled: true
        leftMargin: actor.scene.viewport.atXBeginning ? 0 : actor.scene.viewport.width / 5
        rightMargin: actor.scene.viewport.atXBeginning ? actor.scene.viewport.width / 5 : 0
        onViewportExited: actor.scene.viewport.centerAround(actor);
    }

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

            onBeginContact: actor.airborne = false;
            onEndContact: actor.airborne = true;
        }
    ]

    ActionController { id: actionController }

    StateController {
        id: stateController
        anchors.fill: parent
        actor: actor
    }

    // Allow actor to pass through one-way platforms
    Connections {
        target: actor.world
        onPreSolve: {
            if (contact.fixtureA.type === "one_way_platform") {
                if (actor.airborne)
                    contact.enabled = false;

            } else if (contact.fixtureB.type === "one_way_platform") {
                if (actor.airborne)
                    contact.enabled = false;
            }
        }
    }
}

