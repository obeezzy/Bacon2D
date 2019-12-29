import QtQuick 2.13
import QtQuick.Layouts 1.13
import Bacon2D 1.0

Game {
    id: game
    width: 800
    height: 600
    currentScene: scene
    color: "steelblue"
    deviceScreen {
        requestedOrientation: Qt.LandscapeOrientation
        alwaysOn: true
    }

    TiledScene {
        id: scene
        physics: true
        source: "levels/example.tmx"
        viewport: Viewport { }
        scale: game.isMobile ? game.deviceScreen.availableHeight / game.height : 1
        transformOrigin: Item.Top

        Keys.forwardTo: actor.getEntity()

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

    Item {
        visible: game.isMobile
        parent: game.contentItem
        width: game.isMobile ? game.deviceScreen.availableWidth : game.width
        height: game.isMobile ? game.deviceScreen.availableHeight : game.height
        z: 99999

        RowLayout {
            anchors.fill: parent

            VirtualJoystick {
                Layout.preferredWidth: parent.width / 2
                Layout.fillHeight: true
                keyNavigation: VirtualJoystickKeyNavigation { up: Qt.Key_Launch0 }
            }

            ActorButtonPad {
                Layout.preferredWidth: parent.width / 2
                Layout.fillHeight: true
            }
        }
    }
}
