import QtQuick 2.0
import Bacon2D 1.0

Item {
    id: base
    property Scene scene;

    property double xOffset: 0
    property double yOffset: 0

    property double minYOffset: (- height/2) / base.minScale
    property double maxYOffset: contentHeight - (height/2) / base.minScale
    property double minXOffset: (- width/2) / base.minScale
    property double maxXOffset: contentWidth - (width/2) / base.minScale

    property double visibleWidth: base.width
    property double visibleHeigth: base.height

    readonly property double contentWidth: scene.width
    readonly property double contentHeight: scene.height

    function centerViewIn(xCenter, yCenter){
        if (isNaN(base.minXOffset) || isNaN(base.minYOffset)){
            print("Ignored")
            return
        }
        xOffset = (xCenter - (width/2) / base.minScale ) - x
        yOffset = (yCenter - (height/2) / base.minScale ) - y
    }

    function hScroll(value){
        xOffset += value / base.minScale
    }
    function vScroll(value){
        yOffset += value / base.minScale
    }

    function clamp(min,value,max){
        var temp = Math.max(min,value)
        return Math.min(max, temp)
    }

    onXOffsetChanged: {
        var xOffsetClamp = clamp(minXOffset , xOffset, maxXOffset )
//        console.log(minXOffset + " - " + xOffset + " - " + maxXOffset)
        if (xOffsetClamp !== xOffset){
            xOffset = xOffsetClamp
        }else{
            translator.x = -xOffset * base.minScale
        }
    }
    onYOffsetChanged:{
        var yOffsetClamp = clamp(minYOffset, yOffset, maxYOffset)
//           console.log(minYOffset + " - " + yOffset + " - " + maxYOffset)
        if (yOffsetClamp !== yOffset){
            yOffset = yOffsetClamp
        }else{
            translator.y = -yOffset * base.minScale
        }
    }
    onSceneChanged: {
        if (base.scene){
            base.scene.transform = [scalator ,translator]
        }
    }

    property real xScale: base.width/base.visibleWidth
    property real yScale: base.height/base.visibleHeigth

    property real minScale: Math.min(base.xScale, base.yScale)


    Translate{
        id: translator
    }
    Scale{
        id: scalator
        origin.x: 0
        origin.y: 0

        xScale: base.minScale
        yScale: base.minScale
    }


}
