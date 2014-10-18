import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0

Item {
    id: root
    property string queryString
    signal refresh

    implicitHeight: layout.implicitHeight
    implicitWidth: layout.implicitWidth

    RowLayout {
        anchors.fill: parent

        id: layout
        TextField {
            id: ti
            text: root.queryString
            Layout.fillWidth: true

            Keys.onReturnPressed: {
                queryString = ti.text
                refresh()
            }
            Keys.onEscapePressed: {
                ti.text = queryString
                ti.selectAll()
            }
        }

        Button {
            id: go
            focus: false
            text: "Go"
            onClicked: {
                queryString = ti.text
                refresh()
            }
        }
    }
}
