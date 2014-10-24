import QtQuick 2.0
import QtQuick.Layouts 1.0

Item {
    property var tags
    id: root

    implicitHeight: layout.implicitHeight
    implicitWidth: layout.implicitWidth

    RowLayout {
        id: layout
        anchors.fill: parent

        ListView {
            height: 15
            clip: true
            boundsBehavior: Flickable.StopAtBounds

            orientation: ListView.Horizontal
            spacing: 3
            model: tags
            delegate: Tag {
                text: name
            }

            Image {
                source: "qrc:/images/typicons/tags_to_left.png"
                visible: !parent.atXBeginning
                opacity: 0.5

                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
            }

            Image {
                source: "qrc:/images/typicons/tags_to_right.png"
                visible: !parent.atXEnd
                opacity: 0.5

                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
            }

            Layout.fillWidth: true
        }

        Rectangle {
            height: 15
            width: 15
            radius: 3
            color: ma.containsMouse ? "#580000" : "#b05050"

            Image {
                id: plus
                anchors.centerIn: parent
                source: "qrc:/images/typicons/add_tag.png"
            }

            MouseArea {
                id: ma
                anchors.fill: parent
                hoverEnabled: true

                onClicked: {
                    // TODO
                }
            }
        }
    }
}
