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

    TiledScene {
        id: scene
        physics: true
        source: "levels/example.tmx"
        viewport: Viewport {
            y: yBounds.minimum

            DragHandler {
                enabled: game.isMobile
                minimumPointCount: 3
                xAxis {
                    enabled: true
                    minimum: scene.viewport.xBounds.minimum
                    maximum: scene.viewport.xBounds.maximum
                }

                yAxis {
                    enabled: true
                    minimum: scene.viewport.yBounds.minimum
                    maximum: scene.viewport.yBounds.maximum
                }
            }
        }

        Keys.forwardTo: actor.getEntity()

        VirtualJoystick {
            anchors {
                left: scene.anchorItem.left
                top: scene.anchorItem.top
                bottom: scene.anchorItem.bottom
            }

            width: scene.viewport.width / 2
            keyNavigation: VirtualJoystickKeyNavigation { }
        }

        layers: [
            TiledLayer {
                name: "Player"

                TiledObjectGroup {
                    id: actor
                    entity: Actor { }

                    TiledPropertyMapping { property: "x" }
                    TiledPropertyMapping { property: "y" }
                }
            },

            TiledLayer {
                name: "Ground"

                TiledObjectGroup {
                    entity: Ground { }

                    TiledPropertyMapping { property: "x" }
                    TiledPropertyMapping { property: "y" }
                    TiledPropertyMapping { property: "width" }
                    TiledPropertyMapping { property: "height" }
                }

                TiledObjectGroup {
                    name: "polyground"
                    entity: Polyground { }

                    TiledPropertyMapping { property: "x" }
                    TiledPropertyMapping { property: "y" }
                }
            },

            TiledLayer {
                name: "Coins"

                TiledObjectGroup {
                    entity: Coin { }

                    TiledPropertyMapping { property: "x" }
                    TiledPropertyMapping { property: "y" }
                    TiledPropertyMapping { property: "width" }
                    TiledPropertyMapping { property: "height" }
                }
            },

            TiledLayer {
                name: "Boundaries"

                TiledObjectGroup {
                    entity: LevelBoundaries { }

                    TiledPropertyMapping { property: "x" }
                    TiledPropertyMapping { property: "y" }
                }
            }
        ]
    }
}
