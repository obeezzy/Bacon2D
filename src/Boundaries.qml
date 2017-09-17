import QtQuick 2.0
import Bacon2D 1.0

/*
  This body places 2-pixel wide invisible static bodies around the screen,
  to avoid stuff getting out.
*/

Entity {
    id: item

    transformOrigin: Item.Center
    property alias body: itemBody

    // Body properties
    property alias world: itemBody.world
    property alias target: itemBody.target

    // Fixture properties
    property alias density: itemBody.density
    property alias friction: itemBody.friction
    property alias restitution: itemBody.restitution
    property alias sensor: itemBody.sensor
    property alias groupIndex: itemBody.groupIndex
    property alias categories: itemBody.categories
    //    property var _bounds: item.parent
    anchors.fill: parent
    property double wallWidth: 2
    property variant fixtures: QtObject {
        property alias bottom: _bottom
        property alias top: _top
        property alias left: _left
        property alias right: _right
    }

    Body {
        id: itemBody
        bodyType: Body.Static
        target: item
        property real density
        property real friction
        property real restitution
        property bool sensor
        property int groupIndex: 1
        property int categories: Fixture.Category1
        
        signal beginContact(Fixture other)
        signal endContact(Fixture other)

        Box {
            id: _bottom
            x: 0
            y: 0 + item.height
            width: item.width + 2*item.wallWidth
            height: item.wallWidth
            density: itemBody.density
            friction: itemBody.friction
            restitution: itemBody.restitution
            sensor: itemBody.sensor
            groupIndex: itemBody.groupIndex
            categories: itemBody.categories
        }
        Box {
            id: _top
            x: 0 - item.wallWidth
            y: 0- item.wallWidth
            height: item.wallWidth
            width: item.width + 2*item.wallWidth
            density: itemBody.density
            friction: itemBody.friction
            restitution: itemBody.restitution
            sensor: itemBody.sensor
            groupIndex: itemBody.groupIndex
            categories: itemBody.categories
        }
        Box {
            id: _left
            x: 0 - item.wallWidth
            y: 0 - item.wallWidth
            width: item.wallWidth
            height: item.height + 2*item.wallWidth
            density: itemBody.density
            friction: itemBody.friction
            restitution: itemBody.restitution
            sensor: itemBody.sensor
            groupIndex: itemBody.groupIndex
            categories: itemBody.categories
        }
        Box {
            id: _right
            x: item.width + 0
            y: 0 - item.wallWidth
            width: item.wallWidth
            height: item.height + 2*item.wallWidth
            density: itemBody.density
            friction: itemBody.friction
            restitution: itemBody.restitution
            sensor: itemBody.sensor
            groupIndex: itemBody.groupIndex
            categories: itemBody.categories
        }
    }
}
