import QtQuick 2.0
import QtQuick.Layouts 1.0

Item {
    property var object
    property alias thread: root.object
    id: root
    implicitHeight: layout.implicitHeight + anchors.topMargin + anchors.bottomMargin
    //implicitWidth: layout.implicitWidth +anchors.leftMargin + anchors.rightMargin

    ColumnLayout {
        id: layout
        spacing: 2
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter

        RowLayout {
            SelectableText {
                id: subject
                text: thread.subject

                elide: Text.ElideRight
                Layout.fillWidth: true
                clip: true
            }

            SelectableText {
                id: date
                text: thread.newestDate.toString()
            }
        }

        RowLayout {
            spacing: 10

            SelectableText {
                id: authors
                text: thread.authors

                elide: Text.ElideRight
                Layout.fillWidth: true
                Layout.maximumWidth: implicitWidth
            }

            TagsView {
                tags: thread.tags
                Layout.fillWidth: true
            }
        }
    }
}
