import QtQuick 2.0
import QtQuick.Controls 1.1

Rectangle {
    id: splash

    width: 480
    height: 640

    Loader{
        id: login_page
        anchors.fill: parent
    }

    Timer {
        interval: 100; running: true; repeat: true
        onTriggered: {
            bzIndicator.running = false
            login_page.source = 'login.qml'
        }
    }

    BusyIndicator{
        id: bzIndicator
        running: true

        anchors.centerIn: parent
    }
}
