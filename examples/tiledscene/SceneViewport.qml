import QtQuick 2.13
import Bacon2D 1.0

Viewport {
    id: sceneViewport

    function centerAroundActor() {
        console.log("Center around actor...");
        panToActorAnimation.start();
    }

    y: yBounds.minimum

    DragHandler {
        enabled: sceneViewport.scene.game.isMobile
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

    SequentialAnimation {
        id: panToActorAnimation

        NumberAnimation {
            target: sceneViewport
            property: "x"
            to: sceneViewport.xBounds.minimum
        }
    }
}
