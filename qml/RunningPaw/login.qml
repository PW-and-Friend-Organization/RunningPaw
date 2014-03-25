import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1

Rectangle {
    id: login
    width: 480
    height: 640

    color: "white"

    property int displayMargin : parent.width / 40;
    property int txtPointSize : 15;

    Image {
        id: btn_fb_login
        anchors.centerIn: parent

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
            notificationClient.loginFlag = "1"
        }
    }
}
