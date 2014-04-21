import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1

Rectangle {
    id: exercise_score

    // preset property value
    property int displayMargin : parent.width / 40;
    property int txtPointSize : 15;
    property int txtPointSizeSub : 11;

    Rectangle {
        id: stat_display_title
        Label {
            text: "Experience Stats"
            font.pointSize: txtPointSize
            font.bold: true
            color: "darkblue"
        }
    }

    Column{
        id: stat_display_details
        anchors.top: stat_display_title.bottom
        anchors.topMargin: displayMargin*2

        Row{
            Label {
                text: "Time : "
                font.pointSize: txtPointSize
                color: "darkblue"
            }
            Label {
                id: lbl_time
                font.pointSize: txtPointSize
                color: "darkblue"
                text: ExerciseRecorder.elapedTimeFormatted
            }
        }

//        Row{
//            Label {
//                text: "Distance : "
//                font.pointSize: txtPointSize
//                color: "darkblue"
//            }
//            Label {
//                id: lbl_distance
//                font.pointSize: txtPointSize
//                color: "darkblue"
//                text: ExerciseRecorder.distance
//            }
//        }

        Row{
            Label {
                id: stat_display_details_treasurefound
                text: "Chest Found : "
                font.pointSize: txtPointSize
                color: "darkblue"
            }
            Label {
                id: lbl_chest_found
                font.pointSize: txtPointSize
                color: "darkblue"
                text: MyEvent.pick_count
            }
        }

//        Row{
//            Label {
//                text: "Quest Accomplish : "
//                font.pointSize: txtPointSize
//                color: "darkblue"
//            }
//            Label {
//                id: lbl_quest
//                font.pointSize: txtPointSize
//                color: "darkblue"
//                text: "0"
//            }
//        }

//        Row{
//            Label {
//                id: stat_display_details_mypet
//                text: "Experience Gain : "
//                font.pointSize: txtPointSize
//                color: "darkblue"
//            }
//            Label {
//                id: lbl_exp_gain
//                font.pointSize: txtPointSize
//                color: "darkblue"
//                text: ExerciseRecorder.exp_gain
//            }
//        }
    }

    Button {
        id: btn_home
        text: "HOME"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 100

        onClicked:
        {
            main_stage.source = "home.qml"
            loader_animation.start()
        }
    }
}
