import QtQuick 2.0
import QtQuick.Controls 1.2

Rectangle {
    id: root
    property var message

    color: "red"

    TextArea {
        readOnly: true
        anchors.fill: parent
        text: message.raw
    }

}
