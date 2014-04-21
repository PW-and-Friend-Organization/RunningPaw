import QtQuick 2.0

Rectangle {
    id: exercise_play
    opacity: 0.8

    property int txtPointSize: 15

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
//            Row{
//                Text {
//                    font.pointSize: txtPointSize
//                    text: qsTr("GPS Coor: ")
//                }
//                Text {
//                    id: gpsLocation
//                    font.pointSize: txtPointSize
//                    text: qsTr("%1, %2").arg(ExerciseRecorder.longitude).arg(ExerciseRecorder.latitude)
//                }
//            }

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
        id: pet

        property bool face_direction: false // 1-left, 0-right
        property int  img_seq: 1 // 1-left, 0-right
        property int  x_pos1 : (pet.width/2)-100
        property int  x_pos2 : (pet.width/2)+100

        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height * 0.21
        source: "dog_stage_1/dog_1.png"
        width: 200
        height: 200
        x : x_pos2

        transform: Translate {
            id: pet_move
            x: 0
            Behavior on x { NumberAnimation { duration: 1000; easing.type: Easing.linear } }
        }

        Timer {
            interval: 1000; running: true; repeat: true
            onTriggered: {
                pet_move.x = pet.face_direction ? pet.x_pos1 : pet.x_pos2
                pet.mirror = pet.face_direction ? false : true
                pet.face_direction = !pet.face_direction;
            }
        }
        Timer {
            interval: 250; running: true; repeat: true
            onTriggered: {
                pet.img_seq++;

                switch(pet.img_seq)
                {
                case 1:
                    pet.source = "dog_stage_1/dog_2.png"
                    break;
                case 2:
                    pet.source = "dog_stage_1/dog_1.png"
                    break;
                case 3:
                    pet.source = "dog_stage_1/dog_3.png"
                    break
                case 4:
                    pet.source = "dog_stage_1/dog_1.png"
                    pet.img_seq = 0
                    break;
                }
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
                MyEvent.stop()
                MyEvent.finalizePickCount()
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
