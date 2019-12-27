import QtQuick 2.13
import QtQuick.Layouts 1.13
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
        viewport: SceneViewport { }

        Keys.forwardTo: actor.getEntity()

        // Controller layout
        RowLayout {
            visible: game.isMobile
            anchors.fill: scene.anchorItem

            VirtualJoystick {
                Layout.preferredWidth: scene.viewport.width / 2
                Layout.fillHeight: true
                keyNavigation: VirtualJoystickKeyNavigation { up: Qt.Key_Launch0 }
            }

            ActorButtonPad {
                Layout.preferredWidth: scene.viewport.width / 2
                Layout.fillHeight: true
            }
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
