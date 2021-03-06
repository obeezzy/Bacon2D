/**
 * The MIT License (MIT)
 *
 * Copyright (C) 2012 by INdT
 * Copyright (C) 2014 by Bacon2D
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @author Rodrigo Goncalves de Oliveira <rodrigo.goncalves@openbossa.org>
 * @author Roger Felipe Zanoni da Silva <roger.zanoni@openbossa.org>
 */

import QtQuick 2.13
import Bacon2D 1.0

Game {
    id: game
    width: 400
    height: 250
    deviceScreen {
        requestedOrientation: Qt.LandscapeOrientation
        alwaysOn: true
    }

    currentScene: scene

    ScriptBehavior {
        id: sideScrollBehavior

        script: {
            var newPos = target.x + target.scrollStep
            target.x = newPos > scene.width ? 0 : newPos
            target.x = target.x < 0 ? scene.width : target.x
        }
    }

    ScriptBehavior {
        id: verticalScrollBehavior

        script: {
            var newPos = target.y + target.scrollStep
            target.y = newPos > scene.height ? 0 : newPos
            target.y = target.y < 0 ? scene.height : target.y
        }
    }

    Scene {
        id: scene

        width: parent.width
        height: parent.height
        scale: game.isMobile ? game.deviceScreen.availableHeight / game.height : 1
        transformOrigin: Item.Top

        Entity {
            id: square
            property int scrollStep: 3

            width: 50
            height: 50

            updateInterval: 50

            behavior: sideScrollBehavior

            Rectangle {
                width: 50
                height: 50

                color: "red"
            }
        }
    }

    MouseArea {
        anchors.fill: parent

        onClicked: square.behavior = square.behavior == sideScrollBehavior ? verticalScrollBehavior : sideScrollBehavior
    }
}
