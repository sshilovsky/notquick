import QtQuick 2.0

Rectangle {
    id: root
    width: rootLayout.implicitWidth + 4
    height: rootLayout.implicitHeight + 4
    property string text

    color: "#b05050"
    ColorAnimation {  // animation on tag drop error
        id: error_animation
        target: root
        properties: "color"
        from:  "red"
        to: "#b05050"
        duration: 500
    }

    radius: 3

    Row {
        id: rootLayout
        anchors.centerIn: parent
        spacing: 2

        Image {
            source: root.text == "signed" ? "qrc:/images/typicons/tag_signed.png"
                  : root.text == "attachment" ? "qrc:/images/typicons/tag_attachment.png"
                  : root.text.substring(0, 9) == "notmuch::" ? "qrc:/images/tag_notmuch.png"
                  : ""
        }

        Text {
            id: textItem
            color: "white"
            font.pixelSize: 10
            text: root.text == "signed" ? ""
                : root.text == "attachment" ? ""
                : root.text.substring(0, 9) == "notmuch::" ? root.text.substring(9)
                : root.text
        }

        Rectangle {
            id: close_btn
            visible: tags.canDrop(root.text)
            width: 11
            height: 11
            radius: 3
            color: ma.containsMouse ? "#580000" : " transparent"

            Image {
                source: "qrc:/images/tag_close.png"

                width: 11
                height: 11
            }

            MouseArea {
                id: ma
                anchors.fill: parent
                hoverEnabled: true

                // TODO undo_animation
                onClicked: if(!tags.drop(root.text)) {
                               error_animation.restart()
                               close_btn.visible = false
                           }

            }
        }
    }
}
