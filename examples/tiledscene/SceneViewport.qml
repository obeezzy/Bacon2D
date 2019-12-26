import QtQuick 2.13
import Bacon2D 1.0

Viewport {
    id: viewport
    y: yBounds.minimum

    function centerAroundActor() {
        console.log("Center around actor please!");
    }

    DragHandler {
        enabled: viewport.scene.game.isMobile
        minimumPointCount: 3
        xAxis {
            enabled: true
            minimum: viewport.xBounds.minimum
            maximum: viewport.xBounds.maximum
        }

        yAxis {
            enabled: true
            minimum: viewport.yBounds.minimum
            maximum: viewport.yBounds.maximum
        }
    }

    Component.onCompleted: console.log("SceneViewport=", x, y);
}
