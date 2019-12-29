import QtQuick 2.13
import QtQuick.Controls 2.13
import Bacon2D 1.0

ButtonPad {
    id: buttonPad
    implicitWidth: 300
    implicitHeight: 300

    keyNavigation: ButtonPadKeyNavigation { buttonA: Qt.Key_Up }
    buttonA: jumpButton.pressed

    Button {
        id: jumpButton

        anchors.centerIn: parent
        focusPolicy: Qt.NoFocus

        background: Rectangle {
            implicitWidth: 100
            implicitHeight: 100
            color: jumpButton.pressed ? "red" : "lightgray"
            opacity: .6
            radius: width / 2
        }

        contentItem: Text {
            text: "\u21E7"
            font.pixelSize: 40
            rotation: 45
            color: "black"
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
        }
    }
}
