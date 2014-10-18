import QtQuick 2.0
import Notmuch 1.0
import QtQuick.Controls 1.0

ApplicationWindow {
    visibility: "Maximized"
    visible: true
    title: qsTr("Notquick")

    Item {
        id: tp
        anchors {
            top: parent.top
            bottom: parent.bottom
            left: parent.left
        }
        width: (parent.width - 5) / 2

        QueryInput {
            id: qi
            anchors {
                top: parent.top
                left: parent.left
                right: parent.right
                margins: 5
            }

            queryString: "tag:important"

            onRefresh: updateThreads()
            Component.onCompleted: updateThreads()

            function updateThreads() {
                tv.model = 0
                tv.model = NotmuchDatabase.queryThreads(queryString)
                tv.updateMessages()
            }
        }

        ThreadView {
            id: tv
            spacing: 2
            anchors {
                top: qi.bottom
                bottom: parent.bottom
                left: parent.left
                right: parent.right
                topMargin: 5
                bottomMargin: 5
            }

            onActivated: updateMessages()

            function updateMessages() {
                mv.model = 0
                mv.model = selectedThread.messages
            }
        }
    }

    MessageView {
        id: mv
        spacing: 2
        anchors {
            left: tp.right
            leftMargin: 5
            top: parent.top
            topMargin: 5
            bottom: parent.bottom
            bottomMargin: 5
            right: parent.right
        }
    }

}
