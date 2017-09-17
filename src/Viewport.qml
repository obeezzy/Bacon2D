import QtQuick 2.0
import Bacon2D 1.0

Item {
    property Scene scene;

    property double xOffset: 0
    property double yOffset: 0

    property double minYOffset: - height/2
    property double maxYOffset: contentHeight - height/2
    property double minXOffset: - width/2
    property double maxXOffset: contentWidth - width/2

    readonly property double contentWidth: scene.width
    readonly property double contentHeight: scene.height

    function centerViewIn(xCenter, yCenter){
        xOffset = (xCenter - width/2 ) - x
        yOffset = (yCenter - height/2 ) - y
    }

    function hScroll(value){
        xOffset += value
    }
    function vScroll(value){
        yOffset += value
    }

    function clamp(min,value,max){
        var temp = Math.max(min,value)
        return Math.min(max, temp)
    }

    onXOffsetChanged: {
        var xOffsetClamp = clamp(minXOffset - x, xOffset, maxXOffset - x)
        if (xOffsetClamp != xOffset){
            xOffset = xOffsetClamp
        }else{
            scene.x = -xOffset
        }
    }
    onYOffsetChanged:{
        var yOffsetClamp = clamp(minYOffset - y, yOffset, maxYOffset - y)
        if (yOffsetClamp != yOffset){
            yOffset = yOffsetClamp
        }else{
            scene.y = -yOffset
        }
    }

}
