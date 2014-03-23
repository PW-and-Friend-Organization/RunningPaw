import QtQuick 2.0

Rectangle {
    id: exercise_play
    opacity: 0.8

    property int txtPointSize: 13

    Image {
        width: parent.width
        height: parent.height
        source: "retro_bg_cropped.jpg"
    }

    Rectangle {
        id: recorderViewer
        anchors.top: parent.top
        anchors.topMargin: 50
        anchors.left: parent.left
        anchors.leftMargin: 30

        Column{
            Row{
                Text {
                    font.pointSize: txtPointSize
                    text: qsTr("GPS Coor: ")
                }
                Text {
                    id: gpsLocation
                    font.pointSize: txtPointSize
                    text: qsTr("%1, %2").arg(ExerciseRecorder.longitude).arg(ExerciseRecorder.latitude)
                }
            }

            Row{
                Text {
                    font.pointSize: txtPointSize
                    text: qsTr("Elap Time: ")
                }
                Text {
                    id: elapsTime
                    font.pointSize: txtPointSize
                    text: ExerciseRecorder.elapedTimeFormatted
                }
            }
        }
    }

    Image{
        id: agumon

        property bool face_direction: false // 1-left, 0-right
        property bool stand_sit: false // 1-left, 0-right
        property int  x_pos1 : (agumon.width/2)-100
        property int  x_pos2 : (agumon.width/2)+100

        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height * 0.21
        source: "agumon_stand.png"
        width: 100
        height: 100
        x : x_pos2

        transform: Translate {
            id: agumon_move
            x: 0
            Behavior on x { NumberAnimation { duration: 1000; easing.type: Easing.linear } }
        }

        Timer {
            interval: 1000; running: true; repeat: true
            onTriggered: {
                agumon_move.x = agumon.face_direction ? agumon.x_pos1 : agumon.x_pos2
                agumon.mirror = agumon.face_direction ? false : true
                agumon.face_direction = !agumon.face_direction;
            }
        }
        Timer {
            interval: 250; running: true; repeat: true
            onTriggered: {
                agumon.source = agumon.stand_sit ? "agumon_stand.png" : "agumon_sit.png"
                agumon.stand_sit = !agumon.stand_sit;
            }
        }
    }

    Image {
        id: btn_stop
        width: 100
        height: 100
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 10

        source : "btn_stop_idle.png"

        MouseArea {
            anchors.fill: parent

            onClicked: {
                btn_stop.source = "btn_stop_idle.png"
                main_stage.source = "exercise_score.qml"
                screen.isRunning = false;
                loader_animation.start()
                ExerciseRecorder.stop()
            }
            onPressed: {
                btn_stop.source = "btn_stop_press.png"
            }
            onCanceled: {
                btn_stop.source = "btn_stop_idle.png"
            }
        }
    }
}
