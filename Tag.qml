import QtQuick 2.0

Rectangle {
    id: root
    width: rootLayout.implicitWidth + 4
    height: rootLayout.implicitHeight + 4
    property string text

    color: "#b05050"
    radius: 3

    Row {
        id: rootLayout
        anchors.centerIn: parent
        spacing: 2

        Image {
            source: root.text.substring(0, 9) == "notmuch::" ? "qrc:/images/tag_notmuch.png" : ""
        }

        Text {
            id: textItem
            color: "white"
            font.pixelSize: 10
            text: root.text.substring(0, 9) == "notmuch::" ? root.text.substring(9) : root.text
        }

        Rectangle {
            width: 11
            height: 11
            radius: 3
            color: "transparent"

            Image {
                source: "qrc:/images/tag_close.png"

                width: 11
                height: 11
            }

            MouseArea {
                anchors.fill: parent

                hoverEnabled: true
                onEntered: parent.color = "#580000"
                onExited: parent.color = "transparent"

            }
        }
    }
}
