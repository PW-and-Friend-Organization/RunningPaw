import QtQuick 2.0

Rectangle {
    Text {
        id: txt_logout
        anchors.centerIn: parent
        text: qsTr("Logging out")
    }

    Timer {
        interval: 1000; running: true;
        onTriggered: {
            Qt.quit();
        }
    }
}
