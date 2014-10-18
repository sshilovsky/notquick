import QtQuick 2.0
import QtQuick.Layouts 1.1

Item {
    id: root
    implicitHeight: layout.implicitHeight + anchors.topMargin + anchors.bottomMargin
    //implicitWidth: layout.implicitWidth +anchors.leftMargin + anchors.rightMargin

    ColumnLayout {
        id: layout
        spacing: 2
        anchors.left: parent.left
        anchors.right:  parent.right
        anchors.verticalCenter: parent.verticalCenter

        Text {
            id: subject
            text: thread.subject

            anchors.left: parent.left
            anchors.right: parent.right
            elide: Text.ElideRight
        }

        RowLayout {
            anchors.left: parent.left
            anchors.right: parent.right

            spacing: 10

            Text {
                id: date
                text: thread.datetime
            }

            Text {
                id: authors
                text: thread.authors

                Layout.fillWidth: true
                elide: Text.ElideRight
                Layout.maximumWidth: implicitWidth
            }

            ListView {
                //implicitWidth: 200
                Layout.preferredWidth: (parent.width - authors.implicitWidth) * 0.5
                Layout.fillWidth: true
                height: 15

                orientation: ListView.Horizontal
                spacing: 3
                model: thread.tags
                delegate: Tag {
                    text: name
                }
            }
        }
    }
}
