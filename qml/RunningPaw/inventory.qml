import QtQuick 2.0

Rectangle {
    ListModel {
        id: inventoryModel
        ListElement {
            portrait: "digimon/1.png"
        }
        ListElement {
            portrait: "digimon/2.png"
        }
        ListElement {
            portrait: "digimon/3.png"
        }
        ListElement {
            portrait: "digimon/4.png"
        }
        ListElement {
            portrait: "digimon/5.png"
        }
        ListElement {
            portrait: "digimon/6.png"
        }
        ListElement {
            portrait: "digimon/7.png"
        }
        ListElement {
            portrait: "digimon/8.png"
        }
        ListElement {
            portrait: "digimon/9.png"
        }
        ListElement {
            portrait: "digimon/10.png"
        }
    }

    Component {
        id: inventoryDelegate
        Item {
            width: grid.cellWidth; height: grid.cellHeight
            Image {
                width: grid.cellWidth; height: grid.cellHeight
                source: portrait;
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Rectangle{
                id: highlight
                width: grid.cellWidth; height: grid.cellHeight
                color: "blue"
                opacity: 0.0
            }
            MouseArea {
                anchors.fill: parent

                onClicked: {
                    highlight.opacity = 0.0;
                }
                onPressed: {
                    highlight.opacity = 0.5;
                }
                onCanceled: {
                    highlight.opacity = 0.0;
                }
            }
        }
    }

    GridView {
        id: grid
        anchors.fill: parent
        cellWidth: 100; cellHeight: 100

        model: inventoryModel
        delegate: inventoryDelegate
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        focus: true
    }
}

//GridView {
//    clip: true; model : 30;
//    delegate: Rectangle { width: 80; height: 80; color: Qt.rgba( Math.random(), Math.random(), Math.random(), 1) }
//}

