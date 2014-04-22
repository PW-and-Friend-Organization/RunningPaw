import QtQuick 2.0

Rectangle {
    id: tutorial
    width: 480
    height: 640

    ListModel {
        id: nameModel
        ListElement { name: "1) Connect a headset to your devices"; image: "earphones.png" }
        ListElement { name: "2) Click on the EXERCISE on the left navigation to start!"; image: "empty.png" }
        ListElement { name: "3) Click Play button to start"; image: "btn_play_idle.png"  }
        ListElement { name: "4) Your run has started. Go ahead and walk in the park while listening to the sound produce."; image: "empty.png" }
        ListElement { name: "5) Imagine and visualize the sound. Try responding to it!"; image: "empty.png" }
        ListElement { name: "6) Time to time, you'll hit a jackpot sound! That means you have found some treasure XD"; image: "treasure.png" }
        ListElement { name: "7) Click Stop once you done"; image: "btn_stop_idle.png" }
        ListElement { name: "8) We'll record the amount of treasure found!"; image: "empty.png" }
    }
    Component {
        id: nameDelegate
        Column {
            Text {
                width: tutorial.width
                wrapMode: Text.WordWrap
                text: name;
                font.pointSize: 15
            }
            Image {
                source: image
            }
        }
    }

    ListView {
        anchors.fill: parent
        clip: true
        model: nameModel
        delegate: nameDelegate
        header: bannercomponent
        footer: Rectangle {
            width: parent.width; height: 30;
            gradient: clubcolors
        }
        highlight: Rectangle {
            width: parent.width
            color: "lightgray"
        }
    }

    Component {     //instantiated when header is processed
        id: bannercomponent
        Rectangle {
            id: banner
            width: parent.width; height: 50
            gradient: clubcolors
            border {color: "#9EDDF2"; width: 2}
            Text {
                anchors.centerIn: parent
                text: "Tutorial"
                font.pixelSize: 32
            }
        }
    }
    Gradient {
        id: clubcolors
        GradientStop { position: 0.0; color: "#8EE2FE"}
        GradientStop { position: 0.66; color: "#7ED2EE"}
    }
}
