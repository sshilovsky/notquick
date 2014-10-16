import QtQuick 2.0
import QtQuick.Layouts 1.1

Rectangle {
    id: root
    color: "#90ffff"
    width: parent.width
    height: layout.height
    property QtObject notmuch_thread

    ColumnLayout {
        id: layout
        spacing: 3
        width: parent.width

        Text {
            id: subject
            text: notmuch_thread.subject

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
                text: notmuch_thread.datetime
            }

            Text {
                id: authors
                text: notmuch_thread.authors

                Layout.fillWidth: true
                elide: Text.ElideRight
                Layout.maximumWidth: implicitWidth
            }

            ListView {
                Layout.preferredWidth: (parent.width - authors.implicitWidth) * 0.5
                Layout.fillWidth: true
                height: 15

                orientation: ListView.Horizontal
                spacing: 3
                model: notmuch_thread.tags
                delegate: Tag {
                    text: name
                }
            }
        }
    }
}
