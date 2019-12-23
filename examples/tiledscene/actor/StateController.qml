import QtQuick 2.13
import Bacon2D 1.0
import QtQml.StateMachine 1.13 as DSM

Item {
    id: stateController

    property PhysicsEntity actor: null
    readonly property alias horizontalMirror: sprite.horizontalMirror

    Connections {
        target: actor.controls
        onActionInvoked: {
            switch (action) {
            case "move_left":
                if (eventType === KeyInput.KeyPress)
                    sprite.horizontalMirror = true;
                break;
            case "move_right":
                if (eventType === KeyInput.KeyPress)
                    sprite.horizontalMirror = false;
                break;
            }
        }
    }

    AnimatedSprite {
        id: sprite
        animation: "idle"
        anchors.centerIn: parent
        spriteSheet: SpriteSheet {
            source: "../images/sprite.png"
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
                loops: 1
                spriteStrip: SpriteStrip {
                    frameY: frameHeight
                    finalFrame: 7
                }

                onFinished: {
                    if(actor.airborne && sprite.animation == name)
                        sprite.animation = "freefall"
                }
            },

            SpriteAnimation {
                name: "freefall"
                duration: 500
                loops: Animation.Infinite
                spriteStrip: SpriteStrip {
                    frameY: frameHeight
                    initialFrame: 6
                    finalFrame: 7
                }
            }
        ]
    }

    DSM.StateMachine {
        id: stateMachine
        running: true
        childMode: DSM.State.ParallelStates

        DSM.State {
            id: directionState
            initialState: actor.controls.isPressed("move_left") ? leftDirectionState
                                                                : actor.controls.isPressed("move_right") ? rightDirectionState
                                                                                                         : noDirectionState

            DSM.State {
                id: leftDirectionState
                onEntered: actor.linearVelocity.x = -actor.xStep;

                DSM.SignalTransition {
                    targetState: rightDirectionState
                    signal: actor.controls.actionInvoked
                    guard: actor.controls.isPressed("move_right")
                }

                DSM.SignalTransition {
                    targetState: noDirectionState
                    signal: actor.controls.actionInvoked
                    guard: actor.controls.isReleased( "move_left")
                }
            }

            DSM.State {
                id: rightDirectionState
                onEntered: actor.linearVelocity.x = actor.xStep;

                DSM.SignalTransition {
                    targetState: leftDirectionState
                    signal: actor.controls.actionInvoked
                    guard: actor.controls.isPressed("move_left")
                }

                DSM.SignalTransition {
                    targetState: noDirectionState
                    signal: actor.controls.actionInvoked
                    guard: actor.controls.isReleased("move_right")
                }
            }

            DSM.State {
                id: noDirectionState
                onEntered: actor.linearVelocity.x = 0;

                DSM.SignalTransition {
                    targetState: leftDirectionState
                    signal: actor.controls.actionInvoked
                    guard: actor.controls.isPressed("move_left")
                }

                DSM.SignalTransition {
                    targetState: rightDirectionState
                    signal: actor.controls.actionInvoked
                    guard: actor.controls.isPressed("move_right")
                }
            }
        }

        DSM.State {
            id: spriteState
            initialState: !actor.airborne ? idleState : freefallState

            DSM.State {
                id: idleState

                onEntered: sprite.animation = "idle";

                DSM.SignalTransition {
                    targetState: runState
                    signal: actor.controls.actionInvoked
                    guard: actor.controls.isPressed("move_left")
                }

                DSM.SignalTransition {
                    targetState: runState
                    signal: actor.controls.actionInvoked
                    guard: actor.controls.isPressed("move_right")
                }

                DSM.SignalTransition {
                    targetState: jumpState
                    signal: actor.controls.actionInvoked
                    guard: actor.controls.isPressed("jump")
                }
            }

            DSM.State {
                id: runState
                onEntered: sprite.animation = "run";

                DSM.SignalTransition {
                    targetState: idleState
                    signal: actor.controls.actionInvoked
                    guard: actor.controls.isReleased("move_left") && !actor.controls.isPressed("move_right")
                }

                DSM.SignalTransition {
                    targetState: idleState
                    signal: actor.controls.actionInvoked
                    guard: actor.controls.isReleased("move_right") && !actor.controls.isPressed("move_left")
                }

                DSM.SignalTransition {
                    targetState: jumpState
                    signal: actor.controls.actionInvoked
                    guard: actor.controls.isPressed("jump")
                }

                DSM.SignalTransition {
                    targetState: freefallState
                    signal: actor.onAirborneChanged
                    guard: actor.airborne
                }
            }

            DSM.State {
                id: jumpState
                onEntered: {
                    sprite.animation = "jump";
                    actor.applyLinearImpulse(Qt.point(0, -actor.getMass() * 10), actor.getWorldCenter());
                }

                DSM.SignalTransition {
                    targetState: actor.controls.isPressed("move_left") || actor.controls.isPressed("move_right") ? runState : idleState
                    signal: actor.onAirborneChanged
                    guard: !actor.airborne
                }
            }

            DSM.State {
                id: freefallState
                onEntered: sprite.animation = "freefall";

                DSM.SignalTransition {
                    targetState: actor.controls.isPressed("move_left") || actor.controls.isPressed("move_right") ? runState : idleState
                    signal: actor.onAirborneChanged
                    guard: !actor.airborne
                }
            }
        }
    }
}
