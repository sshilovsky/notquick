import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.2

Item {
    z: parent.z + 1
    id: root
    implicitHeight: layout.implicitHeight + anchors.topMargin + anchors.bottomMargin
    //implicitWidth: layout.implicitWidth + anchors.leftMargin + anchors.rightMargin

    ColumnLayout {
        id: layout
        spacing: 2
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter

        RowLayout {
            SelectableText {
                text: message.from
                Layout.fillWidth: true
                Layout.maximumWidth: contentWidth
            }

            TagsView {
                tags: message.tags
                Layout.fillWidth: true
            }
        }

        SelectableText {
            text: "id:" + message.id
        }
    }

}
