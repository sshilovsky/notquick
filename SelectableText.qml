import QtQuick 2.0

Item {
    id: root
    property alias elide: text.elide
    property string text
    property alias color: text.color

    implicitHeight: text.implicitHeight
    implicitWidth: text.implicitWidth

    Text {
        id: text
        anchors.fill: parent
        text: root.text
        elide: root.elide
    }

    /*TextEdit {
        id: textEdit
        anchors.fill: parent
        text: root.text
        readOnly: true
        selectByMouse: true
        clip: true
        color: "transparent"
    }*/
}
