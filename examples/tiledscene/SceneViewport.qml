import QtQuick 2.13
import Bacon2D 1.0

Viewport {
    id: sceneViewport

    function centerAround(entity) {
        if (entity.x < entity.viewportTracker.leftMargin
                || entity.x > sceneViewport.width - entity.viewportTracker.rightMargin)
            panOnXAxisAnimation.start();
        else if (entity.y > sceneViewport.y)
            panOnYAxisAnimation.start();
    }

    y: yBounds.minimum

    DragHandler {
        enabled: sceneViewport.game.isMobile
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

    NumberAnimation {
        id: panOnXAxisAnimation
        target: sceneViewport
        property: "x"
        to: sceneViewport.atXBeginning ? sceneViewport.xBounds.minimum : sceneViewport.xBounds.maximum
    }

    NumberAnimation {
        id: panOnYAxisAnimation
        target: sceneViewport
        property: "y"
        to: sceneViewport.atYBeginning ? sceneViewport.yBounds.minimum : sceneViewport.yBounds.maximum
    }
}
