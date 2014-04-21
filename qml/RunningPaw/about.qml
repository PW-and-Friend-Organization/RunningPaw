import QtQuick 2.0

Rectangle {
    id: exercise_play

    Column
    {
        anchors.centerIn: parent
        Image {
            id: qt_logo
            source: "qt_mobile.jpg"
        }

        Text {
            text: " "
            font.pointSize: 15
        }

        Image {
            id: digicfc
            source: "digicfc.png"
        }

        Text {
            text: " "
            font.pointSize: 15
        }

        Text {
            text: "PW & Friend Org"
            font.pointSize: 15
        }
    }
}
