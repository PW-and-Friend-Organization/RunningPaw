import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1

Rectangle {
    id: login
    width: 480
    height: 640

    color: "white"

    property int displayMargin : parent.width / 40;
    property int txtPointSize : 25;

//    notificationClient.onLoginPass.connect(onLogin);


    Column {
        anchors.centerIn: parent

        Text {
            anchors.horizontalCenter: parent.horizontalCenter

            text: "Running Paw"
            color: "purple"
            font.family: "Arial"
            font.pointSize: 30
        }

        Image {
            source : "dog_icon_clean.png"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            id: ref_height
            text: " "
            font.pointSize: txtPointSize
        }

        Image {
            id: btn_fb_login
            height: ref_height.height
            width: ref_height.height*5
            anchors.horizontalCenter: parent.horizontalCenter

            source : "login_fb_up.png"

            MouseArea {
                anchors.fill: parent

                onClicked: {
                    btn_fb_login.source = "login_fb_down.png"
                    onLogin()
                }
                onPressed: {
                    btn_fb_login.source = "login_fb_down.png"
                }
                onCanceled: {
                    btn_fb_login.source = "login_fb_up.png"
                }
            }
        }

        Text {
            text: " "
            font.pointSize: txtPointSize
        }

        Text {
            id: press_again
            text: " "
            color: "blue"
            font.pointSize: 15
        }
    }

    Rectangle{
        id: main_page_rect
        width: parent.width
        height: parent.height
        x: parent.width

        Loader{
            id: main_page
            anchors.fill: parent
        }

        Behavior on x { NumberAnimation { duration: 400; easing.type: Easing.OutQuad } }
    }

    function onLogin()
    {
        if( notificationClient.loginFlag === "1" )
        {
            main_page.source = 'main.qml'
            main_page_rect.x = 0
        }
        else
        {
            // go to facebook page
            notificationClient.loginFlag++;

            press_again.text = "Press again to go to home page!!"
        }
    }
}
