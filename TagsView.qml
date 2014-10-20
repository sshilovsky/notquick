import QtQuick 2.0

ListView {
    id: root
    property var tags

    height: 15

    orientation: ListView.Horizontal
    spacing: 3
    model: tags
    delegate: Tag {
        text: name
    }
}
