import QtQuick 2.0
import Notmuch 1.0
import QtQuick.Controls 1.0

ApplicationWindow {
    visibility: "Maximized"
    visible: true
    title: qsTr("Notquick")

    Item {
        id: leftPanel
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

            queryString: "list:notmuch"

            onRefresh: updateThreads()
            Component.onCompleted: updateThreads()

            function updateThreads() { // this is done to implement refreshing on 'Go' click
                threadList.model = 0
                threadList.model = NotmuchDatabase.queryThreads(queryString)
                threadList.updateMessages()
            }
        }

        NotquickList {
            id: threadList
            objectDelegate: ThreadItem {}

            anchors {
                top: qi.bottom
                bottom: parent.bottom
                left: parent.left
                right: parent.right
                topMargin: 5
                bottomMargin: 5
            }

            onAtYEndChanged: if (atYEnd && model) {
                                 model.loadMore()
                             }
        }
    }

    NotquickList {
        id: messageList
        objectDelegate: MessageItem {}
        model: threadList.currentObject.messages

        anchors {
            left: leftPanel.right
            leftMargin: 5
            top: parent.top
            topMargin: 5
            right: parent.right
        }
        height: (parent.height - 15) / 2
    }

    MessageViewer {
        id: messageViewer
        message: messageList.currentObject
        anchors {
            top: messageList.bottom
            left: leftPanel.right
            right: parent.right
            bottom: parent.bottom
            margins: 5
        }
    }

}
