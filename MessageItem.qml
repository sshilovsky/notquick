import QtQuick 2.0

Item {
    id: root
    implicitHeight: layout.implicitHeight + anchors.topMargin + anchors.bottomMargin
    //implicitWidth: layout.implicitWidth +anchors.leftMargin + anchors.rightMargin

    Text {
        id: layout
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        text: message.subject
    }

}
