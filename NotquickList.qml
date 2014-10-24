import QtQuick 2.0

ListView {
    id: root
    readonly property var currentObject: currentItem.myObject
    property Component objectDelegate
    clip: true
    spacing: 2

    delegate: Rectangle {
        property var myObject: object

        color: ListView.isCurrentItem ? "cyan" : index % 2 ? "lightblue" : "lightsteelblue"
        width: parent.width
        height: delegateHere.item.height + 16

        Loader {
            id: delegateHere
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.margins: 8

            sourceComponent: root.objectDelegate

            onLoaded: {
                item.object = myObject
            }
        }

        MouseArea {
            z: root.z - 1
            anchors.fill: parent
            onClicked: root.currentIndex = index
        }
    }
}
