import QtQuick 2.13
import Bacon2D 1.0
import Bacon2D.Private 1.0 as Bacon2DPrivate

Item {
    id: gesturePad

    property GesturePadKeyNavigation keyNavigation: null
    property real threshold: Math.min(50, gesturePad.width)

    signal swipeUp
    signal swipeDown
    signal swipeLeft
    signal swipeRight
    signal tapped
    signal doubleTapped
    signal tripleTapped
    signal tapAndHold

    implicitWidth: 300
    implicitHeight: 300

    DragHandler {
        id: dragHandler
        target: null

        onActiveChanged: {
            if (!active) {
                const xDistance = dragHandler.centroid.position.x - dragHandler.centroid.pressPosition.x;
                const yDistance = dragHandler.centroid.position.y - dragHandler.centroid.pressPosition.y;
                if ( Math.abs(yDistance) > gesturePad.threshold) {
                    if (yDistance < 0) {
                        gesturePad.swipeUp();
                        if (keyNavigation) {
                            keyEventForwarder.pressKey(keyNavigation.swipeUp);
                            keyEventForwarder.releaseKey(keyNavigation.swipeUp);
                        }
                    } else {
                        gesturePad.swipeDown();
                        if (keyNavigation) {
                            keyEventForwarder.pressKey(keyNavigation.swipeDown);
                            keyEventForwarder.releaseKey(keyNavigation.swipeDown);
                        }
                    }
                } else if (Math.abs(xDistance) > gesturePad.threshold) {
                    if (xDistance < 0) {
                        gesturePad.swipeLeft();
                        if (keyNavigation) {
                            keyEventForwarder.pressKey(keyNavigation.swipeLeft);
                            keyEventForwarder.releaseKey(keyNavigation.swipeLeft);
                        }
                    } else {
                        gesturePad.swipeRight();
                        if (keyNavigation) {
                            keyEventForwarder.pressKey(keyNavigation.swipeRight);
                            keyEventForwarder.releaseKey(keyNavigation.swipeRight);
                        }
                    }
                }
            }
        }
    }

    TapHandler {
        id: tapHandler

        onTapped: {
            gesturePad.tapped();
            if (keyNavigation) {
                keyEventForwarder.pressKey(keyNavigation.tap);
                keyEventForwarder.releaseKey(keyNavigation.tap);
            }
        }
        onDoubleTapped: {
            gesturePad.doubleTapped();
            if (keyNavigation) {
                keyEventForwarder.pressKey(keyNavigation.doubleTap);
                keyEventForwarder.releaseKey(keyNavigation.doubleTap);
            }
        }
        onTapCountChanged: {
            if (tapCount === 3) {
                gesturePad.tripleTapped();
                if (keyNavigation) {
                    keyEventForwarder.pressKey(keyNavigation.tripleTap);
                    keyEventForwarder.releaseKey(keyNavigation.tripleTap);
                }
            }
        }
        onLongPressed: {
            gesturePad.tapAndHold();
            if (keyNavigation) {
                keyEventForwarder.pressKey(keyNavigation.tapAndHold);
                keyEventForwarder.releaseKey(keyNavigation.tapAndHold);
            }
        }
    }

    Bacon2DPrivate.KeyEventForwarder { id: keyEventForwarder }
}
