import QtQuick 2.0

Item {
    property var model
    property var selectedThread: threadsList.currentItem.myThread
    property alias spacing: threadsList.spacing
    signal activated(var selectedThread)
    id: root

    ListView {
        anchors.fill: parent

        // TODO ! onContentYChanged:

        id: threadsList
        model: root.model
        delegate: Rectangle {
            property var myThread: thread

            color: threadsList.currentItem == this ? "cyan"
                                                     : index % 2 ? "lightblue" : "lightsteelblue"
            width: parent.width
            height: ti.implicitHeight

            ThreadItem {
                id: ti
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.margins: 8
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    threadsList.currentIndex = index
                    activated(root.selectedThread)
                }
            }
        }
    }
}
