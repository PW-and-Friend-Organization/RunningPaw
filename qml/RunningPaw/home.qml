import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1

Rectangle {
    id: home_page
    width: 480
    height: 640
    opacity: 0.8

    // preset property value
    property int displayMargin : parent.width / 40;
    property int txtPointSize : 15;
    property int txtPointSizeSub : 11;

    Image {
        width: parent.width
        height: parent.height
        source: "retro_bg_cropped.jpg"
    }

    Rectangle{
        id: mypet_stats
        anchors.top: parent.top
        anchors.topMargin: displayMargin
        anchors.left: parent.left
        anchors.leftMargin: displayMargin
        color: "white"
        //opacity: 1.0
        width: 300
        height: column_mypet_stat.height + displayMargin*2

        Rectangle{
            id: mypet_stats_frame
            anchors.fill: parent
            anchors.margins: displayMargin
            opacity: 0
        }
        Column{
            id: column_mypet_stat
            anchors.top: mypet_stats_frame.top
            anchors.left: mypet_stats_frame.left

            Text{
                text: FacebookClient.name
                font.bold: true
                font.pointSize: txtPointSize
            }

            Row{
                id: home_stat_row2
                Text{
                    text: "Treasure Found : "
                    font.bold: true
                    font.pointSize: txtPointSizeSub
                }
                Text{
                    text: FacebookClient.found
                    font.bold: true
                    font.italic: true
                    font.pointSize: txtPointSizeSub
                }
            }

            Text{
                text: "   "
                font.pointSize: txtPointSizeSub
            }

            ProgressBar {
                id: mypet_experience_bar
                anchors.topMargin: displayMargin
                anchors.horizontalCenter: mypet_stats_frame.horizontalCenter
                value: 99
                minimumValue: 0.0
                maximumValue: 100.0
                style: ProgressBarStyle {
                    background: Rectangle {
                        radius: 2
                        color: "lightgray"
                        border.color: "gray"
                        border.width: 1
                        implicitWidth: 250
                        implicitHeight: 15
                    }
                    progress: Rectangle {
                        color: "lightsteelblue"
                        border.color: "steelblue"
                    }
                }
            }
        }
    }

    Image{
        id: pet

        property bool face_direction: false // 1-left, 0-right
        property int  img_seq: 1 // 1-left, 0-right
        property int  x_pos1 : (pet.width/2)-50
        property int  x_pos2 : (pet.width/2)+50

        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height * 0.21
        source: "dog_stage_1/dog_1.png"
        width: 200
        height: 200
        x : x_pos2

        transform: Translate {
            id: pet_move
            x: 0
            Behavior on x { NumberAnimation { duration: 3000; easing.type: Easing.linear } }
        }

        Timer {
            interval: 3000; running: true; repeat: true
            onTriggered: {
                pet_move.x = pet.face_direction ? pet.x_pos1 : pet.x_pos2
                pet.mirror = pet.face_direction ? false : true
                pet.face_direction = !pet.face_direction;
            }
        }
        Timer {
            interval: 500; running: true; repeat: true
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
}
