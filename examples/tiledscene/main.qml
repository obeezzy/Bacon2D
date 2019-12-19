import QtQuick 2.13
import Bacon2D 1.0

Game {
    id: game
    width: 800
    height: 600
    currentScene: scene

    TiledScene {
        id: scene
        physics: true
        source: "levels/example.tmx"
        viewport: Viewport {
            yOffset: scene.height - game.height
            width: game.width
            height: game.height
        }

        layers: [
            TiledLayer {
                name: "Player"

                TiledObjectGroup {
                    id: player
                    entity: Dog { }

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

        // Key handling
        Keys.onPressed: {
            if (!event.isAutoRepeat) {
                switch (event.key) {
                case Qt.Key_Left:
                    player.getEntity().handleEvent("left", "press");
                    break;
                case Qt.Key_Right:
                    player.getEntity().handleEvent("right", "press");
                    break;
                case Qt.Key_Up:
                    player.getEntity().handleEvent("up", "press");
                    break;
                }
            }

            event.accepted = true;
        }

        Keys.onReleased: {
            if (!event.isAutoRepeat) {
                switch (event.key) {
                case Qt.Key_Left:
                    player.getEntity().handleEvent("left", "release");
                    break;
                case Qt.Key_Right:
                    player.getEntity().handleEvent("right", "release");
                    break;
                case Qt.Key_Up:
                    player.getEntity().handleEvent("up", "release");
                    break;
                }
            }

            event.accepted = true;
        }
    }
}
