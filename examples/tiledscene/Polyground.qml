import QtQuick 2.13
import Bacon2D 1.0

PhysicsEntity {
    entityType: "polyground"

    fixtures: Polygon {
        readonly property string type: "one_way_platform"
        density: 1
        restitution: 0
        friction: 1
    }
}
