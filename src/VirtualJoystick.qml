import QtQuick 2.13
import Bacon2D 1.0
import Bacon2D.Private 1.0 as BaconPrivate

Item {
    id: virtualJoystick

    enum Direction {
        None, Up, Down, Left, Right
    }

    readonly property alias handle: handle
    readonly property alias handleBorder: handleBorder
    readonly property real angle: handle.angle
    readonly property real axisX: handle.axisX
    readonly property real axisY: handle.axisY
    readonly property int direction: handle.direction
    property real deadZone: 0
    property VirtualJoystickKeyNavigation keyNavigation: null

    implicitWidth: 300
    implicitHeight: 300

    Rectangle {
        id: handle

        property int direction: VirtualJoystick.Direction.None
        property real axisX: 0
        property real axisY: 0
        property real angle: 0

        function updateAxesAndDirection(point) {
            const limitedPoint = handleBorder.limit(point);
            const minPoint = Qt.point(handleBorder.center.x - handleBorder.radius,
                                      handleBorder.center.y - handleBorder.radius);
            const maxPoint = Qt.point(handleBorder.center.x + handleBorder.radius,
                                      handleBorder.center.y + handleBorder.radius);
            handle.axisX = ((limitedPoint.x - minPoint.x) / (maxPoint.x - minPoint.x) - .5) * 2;
            handle.axisY = ((limitedPoint.y - minPoint.y) / (maxPoint.y - minPoint.y) - .5) * 2;
            const radians = Math.atan2(handle.axisY, handle.axisX);
            handle.angle = handleBorder.radiansToDegrees(radians);

            if (tapHandler.pressed || (!tapHandler.pressed && !dragHandler.active)
                    || handleBorder.withinDeadZone(limitedPoint))
                handle.direction = VirtualJoystick.Direction.None;
            else if (dragHandler.active && handle.angle >= 225 && handle.angle < 315)
                handle.direction = VirtualJoystick.Direction.Up;
            else if (dragHandler.active && handle.angle >= 135 && handle.angle < 225)
                handle.direction = VirtualJoystick.Direction.Left;
            else if (dragHandler.active && ((handle.angle >= 315 && handle.angle < 360)
                                            || (handle.angle > 0 && handle.angle < 45)))
                handle.direction = VirtualJoystick.Direction.Right;
            else if (dragHandler.active && handle.angle >= 45 && handle.angle < 135)
                handle.direction = VirtualJoystick.Direction.Down;

        }

        function resetAxesAndDirection() {
            handle.axisX = 0;
            handle.axisY = 0;
            handle.angle = 0;
            handle.direction = VirtualJoystick.Direction.None;
        }

        x: {
            if (tapHandler.pressed)
                tapHandler.point.position.x - radius
            else if (dragHandler.active)
                handleBorder.limit(dragHandler.centroid.position).x - radius
            else
                virtualJoystick.width / 2 - width / 2
        }
        y: {
            if (tapHandler.pressed)
                tapHandler.point.position.y - radius
            else if (dragHandler.active)
                handleBorder.limit(dragHandler.centroid.position).y - radius
            else
                virtualJoystick.height / 2 - height / 2
        }
        visible: tapHandler.pressed || dragHandler.active
        implicitWidth: 100
        implicitHeight: 100
        color: "lightgray"
        opacity: .5
        radius: width / 2
        onDirectionChanged: {
            if (!virtualJoystick.keyNavigation)
                return;

            switch (handle.direction) {
            case VirtualJoystick.Direction.Up:
                if (keyEventForwarder.isPressed(virtualJoystick.keyNavigation.downKey))
                    keyEventForwarder.releaseKey(virtualJoystick.keyNavigation.downKey);
                keyEventForwarder.pressKey(virtualJoystick.keyNavigation.upKey);
                break;
            case VirtualJoystick.Direction.Left:
                if (keyEventForwarder.isPressed(virtualJoystick.keyNavigation.rightKey))
                    keyEventForwarder.releaseKey(virtualJoystick.keyNavigation.rightKey);
                keyEventForwarder.pressKey(virtualJoystick.keyNavigation.leftKey);
                break;
            case VirtualJoystick.Direction.Right:
                if (keyEventForwarder.isPressed(virtualJoystick.keyNavigation.leftKey))
                    keyEventForwarder.releaseKey(virtualJoystick.keyNavigation.leftKey);
                keyEventForwarder.pressKey(virtualJoystick.keyNavigation.rightKey);
                break;
            case VirtualJoystick.Direction.Down:
                if (keyEventForwarder.isPressed(virtualJoystick.keyNavigation.upKey))
                    keyEventForwarder.releaseKey(virtualJoystick.keyNavigation.upKey);
                keyEventForwarder.pressKey(virtualJoystick.keyNavigation.downKey);
                break;
            default:
                keyEventForwarder.releaseAllKeys();
                break;
            }
        }
    }

    Rectangle {
        id: handleBorder

        property point center: Qt.point(x + radius, y + radius)
        property real margin: 50

        function distance(dot1, dot2) {
            const x1 = dot1.x,
            y1 = dot1.y,
            x2 = dot2.x,
            y2 = dot2.y;
            return Math.sqrt(Math.pow(x1 - x2, 2) + Math.pow(y1 - y2, 2));
        }

        function limit(point, radius) {
            if (radius === undefined)
                radius = handleBorder.radius;
            const dist = distance(point, handleBorder.center);
            let result = null;
            if (dist <= radius) {
                result = Qt.point(point.x, point.y);
            } else {
                point.x = point.x - handleBorder.center.x;
                point.y = point.y - handleBorder.center.y;
                const radians = Math.atan2(point.y, point.x);
                result = Qt.point(Math.cos(radians) * radius + handleBorder.center.x,
                                  Math.sin(radians) * radius + handleBorder.center.y);
            }

            return result;
        }

        function clamp(num, minimum, maximum) {
            return Math.max(Math.min(num, Math.max(minimum, maximum)), Math.min(minimum, maximum));
        }

        function withinDeadZone(point) {
            return limit(point, handleBorder.radius * handleBorder.clamp(virtualJoystick.deadZone, 0, 1)).x === point.x
                    && limit(point, handleBorder.radius * handleBorder.clamp(virtualJoystick.deadZone, 0, 1)).y === point.y;
        }

        function radiansToDegrees(radians) {
            if (radians >= 0)
                return radians * 180 / Math.PI;

            return 180 * (1 + (1 + radians / Math.PI));
        }

        implicitWidth: handle.width + handleBorder.margin
        implicitHeight: handle.height + handleBorder.margin
        visible: handle.visible
        color: "transparent"
        radius: width / 2
        opacity: handle.opacity
        border {
            width: 2
            color: handle.color
        }
    }

    DragHandler {
        id: dragHandler
        property point handleCenter: Qt.point(handle.x + handle.radius,
                                              handle.y + handle.radius)

        target: null

        Binding on handleCenter {
            when: dragHandler.active
            value: dragHandler.centroid.position
        }

        onHandleCenterChanged: {
            if (active)
                handle.updateAxesAndDirection(centroid.position);
            else
                handle.resetAxesAndDirection();
        }
    }

    TapHandler {
        id: tapHandler
        onPressedChanged: {
            if (pressed) {
                handleBorder.center = Qt.point(point.pressPosition.x,
                                               point.pressPosition.y);
                handleBorder.x = point.position.x - handleBorder.radius;
                handleBorder.y = point.position.y - handleBorder.radius;
                handle.updateAxesAndDirection(point.position);
            }
        }
    }

    BaconPrivate.KeyEventForwarder {
        id: keyEventForwarder
    }
}
