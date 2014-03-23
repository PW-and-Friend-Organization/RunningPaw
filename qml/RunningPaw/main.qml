import QtQuick 2.0

Rectangle {
    id: screen

    color: "black"

    // preset property value
    property int displayMargin : parent.width / 40;
    property int txtPointSize : 15;
    property int txtPointSizeMenu : 18;
    property int txtPointSizeTitle : 25;

    property bool menu_shown: false
    property bool isRunning: false

    /* this rectangle contains the "menu" */
    Rectangle {
        id: menu_view_
        anchors.fill: parent
        color: "#303030";
        opacity: screen.menu_shown ? 1 : 0

        Behavior on opacity { NumberAnimation { duration: 300 } }

        /* this is my sample menu content (TODO: replace with your own)  */
        ListView {
            anchors { fill: parent; margins: 22 }
            model: ContextMenuList
            delegate: Rectangle {
                height: contextMenuText.height + displayMargin ; width: parent.width;
                color: "#303030";
                Text {
                    id: contextMenuText
                    anchors { left: parent.left; leftMargin: displayMargin; verticalCenter: parent.verticalCenter }
                    color: "white"; font.pointSize: txtPointSizeMenu; text: menu_name
                }
                Rectangle {
                    height: 2; width: parent.width * 0.85; color: "gray";
                    anchors { left: parent.left; bottom: parent.bottom }
                }
                MouseArea {
                    anchors.fill: parent
                    enabled: screen.menu_shown

                    onClicked: {
                        parent.color = "#303030"
                        postMessage(menu_param)

                        if( menu_param == "exercise.qml" && screen.isRunning )
                            main_stage.source = "exercise_play.qml"
                        else
                            main_stage.source = menu_param
                        screen.onMenu()
                    }
                    onPressed: {
                        parent.color = "#101010"
                    }
                    onCanceled: {
                        parent.color = "#303030"
                    }
                }
            }
        }
    }

    /* this rectangle contains the "normal" view in your app */
    Rectangle {
        id: normal_view_
        anchors.fill: parent
        color: "white"

        /* this is what moves the normal view aside */
        transform: Translate {
            id: game_translate_
            x: 0
            Behavior on x { NumberAnimation { duration: 400; easing.type: Easing.OutQuad } }
        }

        /* quick and dirty menu "button" for this demo (TODO: replace with your own) */
        Rectangle {
            id: menu_bar_
            anchors.top: parent.top
            width: parent.width; height: menu_title.height * 1.5
            gradient: Gradient {
                        GradientStop { position: 0.0; color: "#6767CF" }
                        GradientStop { position: 0.5; color: "#4D4DA1" }
                    }
            Rectangle {
                id: menu_button_
                anchors {left: parent.left; verticalCenter: parent.verticalCenter; margins: 24 }
                color: "white"; width: menu_title.height ; height: menu_title.height; smooth: true
                scale: ma_.pressed ? 1.2 : 1
                Text { anchors.centerIn: parent; font.pointSize: txtPointSizeTitle; text: "="; color: "#6767CF" }

                MouseArea { id: ma_; anchors.fill: parent;
                    onClicked:{
                        screen.onMenu()
                    }
                }
            }
            Text {
                id: menu_title
                anchors{
                    left: menu_button_.right
                    leftMargin: displayMargin * 2
                    verticalCenter: parent.verticalCenter;
                }
                font.pointSize: txtPointSizeTitle
                text: "Running Paws"
                color: "white"
            }
        }


        /* this is my sample "normal" contant (TODO: replace with your own)  */
        Rectangle{
            id: loader_rect
            property int maxWidth: parent.width - 60
            width: maxWidth

            state: "NORMAL"
            anchors { top: menu_bar_.bottom; bottom: parent.bottom; left: parent.left; margins: 30 } //; right: parent.right

            Loader {
                id: main_stage
                anchors.fill: parent
                source: "home.qml"
            }

            SequentialAnimation on width {
                id: loader_animation

                // Move from minHeight to maxHeight in 300ms, using the OutExpo easing function
                NumberAnimation {
                    from: loader_rect.maxWidth; to: 0
                    easing.type: Easing.OutExpo; duration: 200
                }

                // Then move back to minHeight in 1 second, using the OutBounce easing function
                NumberAnimation {
                    from: 0; to: loader_rect.maxWidth
                    easing.type: Easing.OutBounce; duration: 500
                }

                // Then pause for 500ms
                PauseAnimation { duration: 500 }
            }
        }


        /* put this last to "steal" touch on the normal window when menu is shown */
        MouseArea {
            anchors.fill: parent
            enabled: screen.menu_shown
            onClicked: screen.onMenu();
        }
    }

    /* this functions toggles the menu and starts the animation */
    function onMenu()
    {
        game_translate_.x = screen.menu_shown ? 0 : screen.width * 0.9
        screen.menu_shown = !screen.menu_shown;
    }
}
