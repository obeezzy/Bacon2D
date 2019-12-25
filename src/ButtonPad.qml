import QtQuick 2.13
import Bacon2D 1.0
import Bacon2D.Private 1.0 as BaconPrivate

Item {
    id: buttonPad

    property ButtonPadKeyNavigation keyNavigation: null
    property bool buttonL1: false
    property bool buttonL2: false
    property bool buttonL3: false
    property bool buttonR1: false
    property bool buttonR2: false
    property bool buttonR3: false
    property bool buttonA: false
    property bool buttonB: false
    property bool buttonCenter: false
    property bool buttonDown: false
    property bool buttonGuide: false
    property bool buttonLeft: false
    property bool buttonRight: false
    property bool buttonSelect: false
    property bool buttonStart: false
    property bool buttonUp: false
    property bool buttonX: false
    property bool buttonY: false

    implicitWidth: 300
    implicitHeight: 300

    onButtonL1Changed: {
        if (keyNavigation) {
            if (buttonPad.buttonL1)
                keyEventForwarder.pressKey(keyNavigation.buttonL1);
            else
                keyEventForwarder.releaseKey(keyNavigation.buttonL1);
        }
    }

    onButtonL2Changed: {
        if (keyNavigation) {
            if (buttonPad.buttonL2)
                keyEventForwarder.pressKey(keyNavigation.buttonL2);
            else
                keyEventForwarder.releaseKey(keyNavigation.buttonL2);
        }
    }

    onButtonL3Changed: {
        if (keyNavigation) {
            if (buttonPad.buttonL3)
                keyEventForwarder.pressKey(keyNavigation.buttonL3);
            else
                keyEventForwarder.releaseKey(keyNavigation.buttonL3);
        }
    }

    onButtonR1Changed: {
        if (keyNavigation) {
            if (buttonPad.buttonR1)
                keyEventForwarder.pressKey(keyNavigation.buttonR1);
            else
                keyEventForwarder.releaseKey(keyNavigation.buttonR1);
        }
    }

    onButtonR2Changed: {
        if (keyNavigation) {
            if (buttonPad.buttonR2)
                keyEventForwarder.pressKey(keyNavigation.buttonR2);
            else
                keyEventForwarder.releaseKey(keyNavigation.buttonR2);
        }
    }

    onButtonR3Changed: {
        if (keyNavigation) {
            if (buttonPad.buttonR3)
                keyEventForwarder.pressKey(keyNavigation.buttonR3);
            else
                keyEventForwarder.releaseKey(keyNavigation.buttonR3);
        }
    }

    onButtonAChanged: {
        if (keyNavigation) {
            if (buttonPad.buttonA)
                keyEventForwarder.pressKey(keyNavigation.buttonA);
            else
                keyEventForwarder.releaseKey(keyNavigation.buttonA);
        }
    }

    onButtonBChanged: {
        if (keyNavigation) {
            if (buttonPad.buttonB)
                keyEventForwarder.pressKey(keyNavigation.buttonB);
            else
                keyEventForwarder.releaseKey(keyNavigation.buttonB);
        }
    }

    onButtonCenterChanged: {
        if (keyNavigation) {
            if (buttonPad.buttonCenter)
                keyEventForwarder.pressKey(keyNavigation.buttonCenter);
            else
                keyEventForwarder.releaseKey(keyNavigation.buttonCenter);
        }
    }

    onButtonDownChanged: {
        if (keyNavigation) {
            if (buttonPad.buttonDown)
                keyEventForwarder.pressKey(keyNavigation.buttonDown);
            else
                keyEventForwarder.releaseKey(keyNavigation.buttonDown);
        }
    }

    onButtonGuideChanged: {
        if (keyNavigation) {
            if (buttonPad.buttonGuide)
                keyEventForwarder.pressKey(keyNavigation.buttonGuide);
            else
                keyEventForwarder.releaseKey(keyNavigation.buttonGuide);
        }
    }

    onButtonLeftChanged: {
        if (keyNavigation) {
            if (buttonPad.buttonLeft)
                keyEventForwarder.pressKey(keyNavigation.buttonLeft);
            else
                keyEventForwarder.releaseKey(keyNavigation.buttonLeft);
        }
    }

    onButtonRightChanged: {
        if (keyNavigation) {
            if (buttonPad.buttonRight)
                keyEventForwarder.pressKey(keyNavigation.buttonRight);
            else
                keyEventForwarder.releaseKey(keyNavigation.buttonRight);
        }
    }

    onButtonSelectChanged: {
        if (keyNavigation) {
            if (buttonPad.buttonSelect)
                keyEventForwarder.pressKey(keyNavigation.buttonSelect);
            else
                keyEventForwarder.releaseKey(keyNavigation.buttonSelect);
        }
    }

    onButtonStartChanged: {
        if (keyNavigation) {
            if (buttonPad.buttonStart)
                keyEventForwarder.pressKey(keyNavigation.buttonStart);
            else
                keyEventForwarder.releaseKey(keyNavigation.buttonStart);
        }
    }

    onButtonUpChanged: {
        if (keyNavigation) {
            if (buttonPad.buttonUp)
                keyEventForwarder.pressKey(keyNavigation.buttonUp);
            else
                keyEventForwarder.releaseKey(keyNavigation.buttonUp);
        }
    }

    onButtonXChanged: {
        if (keyNavigation) {
            if (buttonPad.buttonX)
                keyEventForwarder.pressKey(keyNavigation.buttonX);
            else
                keyEventForwarder.releaseKey(keyNavigation.buttonX);
        }
    }

    onButtonYChanged: {
        if (keyNavigation) {
            if (buttonPad.buttonY)
                keyEventForwarder.pressKey(keyNavigation.buttonY);
            else
                keyEventForwarder.releaseKey(keyNavigation.buttonY);
        }
    }

    BaconPrivate.KeyEventForwarder { id: keyEventForwarder }
}
