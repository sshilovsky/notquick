import QtQuick 2.3
import QtQuick.Controls 1.2
import Notmuch 1.0
import QtQuick.Layouts 1.1

ApplicationWindow {
    visible: true
    width: 600
    height: 480
    title: qsTr("Hello World")

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 50

        RowLayout {
            TextField {
                id: queryText
                text: "tag:important"
                Layout.fillWidth: true
            }

            Button {
                text: "Go"
                onClicked: threadsList.model = NotmuchDatabase.query_threads(queryText.text)
            }
        }

        ListView {
            //clip: true // TODO !
            Layout.fillHeight: true
            Layout.fillWidth: true

            id: threadsList
            spacing: 2
            model: NotmuchDatabase.query_threads("tag:important")
            delegate: ThreadItem {
                notmuch_thread: thread
            }
        }

    }
}
