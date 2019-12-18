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
    width: 800
    height: 600

    currentScene: scene

    property int numberOfSprites: 50

    Component {
        id: spriteComponent

        AnimatedSprite {
            animation: "explosion"
            spriteSheet: SpriteSheet {
                source: "explosion.png"
                horizontalFrameCount: 4
            }

            animations: SpriteAnimation {
                name: "explosion"
                duration: 400
                loops: Animation.Infinite
            }
        }
    }

    Scene {
        id: scene

        width: game.width
        height: game.height

        Component.onCompleted: {
            var spriteObject;

            for (var i = 0; i < game.numberOfSprites; i++) {
                spriteObject = spriteComponent.createObject(scene)
                spriteObject.x = Math.random() * game.width
                spriteObject.y = Math.random() * game.height
            }
        }
    }
}
