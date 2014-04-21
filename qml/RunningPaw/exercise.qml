import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1

Rectangle {
    id: exercise_page

    // preset property value
    property int displayMargin : parent.width / 40;
    property int txtPointSize : 15;
    property int txtPointSizeSub : 11;

    Image {
        id: btn_start
        width: 100
        height: 100
        source: "btn_play_idle.png"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top

        MouseArea {
            anchors.fill: parent

            onClicked: {
                btn_start
                btn_start.source = "btn_play_idle.png"
                main_stage.source = "exercise_play.qml"
                screen.isRunning = true
                loader_animation.start()
                ExerciseRecorder.start()
                MyEvent.start()
            }
            onPressed: {
                btn_start.source = "btn_play_press.png"
            }
            onCanceled: {
                btn_start.source = "btn_play_idle.png"
            }
        }
    }

    Rectangle{
        anchors{top: btn_start.bottom; bottom: parent.bottom; left: parent.left; right: parent.right }
        ListModel {
            id: questModel
            ListElement{ quest_title:"50m sprints"; quest_desc:"Run 50 meters in 10 seconds"}
            ListElement{ quest_title:"30min jogs"; quest_desc:"Run at least for 30 minutes without stop"}
            ListElement{ quest_title:"50m sprints"; quest_desc:"Run 50 meters in 10 seconds"}
            ListElement{ quest_title:"50m sprints"; quest_desc:"Run 50 meters in 10 seconds"}
            ListElement{ quest_title:"50m sprints"; quest_desc:"Run 50 meters in 10 seconds"}
            ListElement{ quest_title:"50m sprints"; quest_desc:"Run 50 meters in 10 seconds"}
        }
        Component {
            id: questDelegate
            Row{
                CheckBox{
                }
                Column {
                    Text { text: quest_title; font.pointSize: txtPointSize; font.bold: true }
                    Text { text: quest_desc; font.pointSize: txtPointSizeSub }
                }
            }
        }

        ListView {
           anchors.fill: parent
           model: questModel
           delegate: questDelegate
        }
    }
}
