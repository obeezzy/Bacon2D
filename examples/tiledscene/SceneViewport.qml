import QtQuick 2.13
import Bacon2D 1.0

Viewport {
    id: sceneViewport
    y: yBounds.minimum

    DragHandler {
        enabled: game.isMobile
        minimumPointCount: 3
        xAxis {
            enabled: true
            minimum: sceneViewport.xBounds.minimum
            maximum: sceneViewport.xBounds.maximum
        }

        yAxis {
            enabled: true
            minimum: sceneViewport.yBounds.minimum
            maximum: sceneViewport.yBounds.maximum
        }
    }
}
