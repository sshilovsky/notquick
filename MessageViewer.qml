import QtQuick 2.0
import QtQuick.Controls 1.2
import Notquick 1.0

Rectangle {
    id: root
    property var message
    property var entity: message.createMimeEntity()

    color: "red"

    TextArea {
        readOnly: true
        anchors.fill: parent
        text: entity.body
    }

}
