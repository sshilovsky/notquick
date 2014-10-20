import QtQuick 2.0
import QtQuick.Layouts 1.1

Item {
    z: parent.z + 1
    id: root
    implicitHeight: layout.implicitHeight + anchors.topMargin + anchors.bottomMargin
    //implicitWidth: layout.implicitWidth +anchors.leftMargin + anchors.rightMargin

    ColumnLayout {
        id: layout
        spacing: 2
        anchors.left: parent.left
        anchors.right: parent.right
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

            TagsView {
                tags: thread.tags
                Layout.fillWidth: true
            }

        }
    }
}
