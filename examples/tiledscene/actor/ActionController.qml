import QtQuick 2.13
import Bacon2D 1.0

Item {
    id: actionController

    function isPressed(action) { return keyInput.isPressed(action); }
    function isReleased(action) { return keyInput.isReleased(action); }
    signal actionInvoked(string action, int eventType)

    Keys.forwardTo: keyInput

    KeyInput {
        id: keyInput

        KeyAction { action: "move_left"; key: Qt.Key_Left }
        KeyAction { action: "move_right"; key: Qt.Key_Right }
        KeyAction { action: "jump"; key: Qt.Key_Up }

        onActionInvoked: actionController.actionInvoked(action, eventType);
    }
}
