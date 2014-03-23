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

    //
    // Input for UserName
    //
    Text {
        id: txt_username
        anchors.top: input_username.top
        anchors.right: input_username.left
        anchors.rightMargin: displayMargin

        text: qsTr("Username")
        font.pointSize: txtPointSize
        color: "black"
    }

    TextField{
        id : input_username
        font.pointSize: txtPointSize

        anchors.top: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: displayMargin

        style: TextFieldStyle {
            textColor: "black"
            background: Rectangle {
                radius: 2
                implicitWidth: txt_username.width * 1.50
                implicitHeight: txt_username.height * 1.25
                border.color: "#333"
                border.width: 1
            }
        }
    }

    //
    // Input for Password
    //
    Text {
        id: txt_password
        anchors.top: input_username.bottom
        anchors.topMargin: displayMargin
        anchors.left: txt_username.left

        text: qsTr("Password")
        font.pointSize: txtPointSize
        color: "black"
    }

    TextField{
        id : input_password
        font.pointSize: txtPointSize
        echoMode: TextInput.Password

        anchors.top: input_username.bottom
        anchors.topMargin: displayMargin
        anchors.left: input_username.left

        style: TextFieldStyle {
            textColor: "black"
            background: Rectangle {
                radius: 2
                implicitWidth: input_username.width
                implicitHeight: txt_password.height * 1.25
                border.color: "#333"
                border.width: 1
            }
        }
    }

    Button{
        id: btn_login
        text: "Login"
        anchors.left: input_password.left
        anchors.top: input_password.bottom
        anchors.topMargin: displayMargin


        style: ButtonStyle {
                background: Rectangle {
                    implicitWidth: input_username.width / 2
                    implicitHeight: txt_password.height * 1.25
                    border.width: control.activeFocus ? 2 : 1
                    border.color: "#888"
                    radius: 4
                    gradient: Gradient {
                        GradientStop { position: 0 ; color: control.pressed ? "#ccc" : "#eee" }
                        GradientStop { position: 1 ; color: control.pressed ? "#aaa" : "#ccc" }
                    }
                }
            }

        onClicked:
        {
            console.log('login clicked')
            if( input_password.text != '' && input_password !== '')
            {
                console.log('login translate')
                main_page.source = 'main.qml'
                main_page_rect.x = 0
            }
        }
    }

    Button{
        id: btn_register
        text: "Register"
        anchors.left: btn_login.left
        anchors.top: btn_login.bottom
        anchors.topMargin: displayMargin


        style: ButtonStyle {
                background: Rectangle {
                    implicitWidth: input_username.width / 2
                    implicitHeight: txt_password.height * 1.25
                    border.width: control.activeFocus ? 2 : 1
                    border.color: "#888"
                    radius: 4
                    gradient: Gradient {
                        GradientStop { position: 0 ; color: control.pressed ? "#ccc" : "#eee" }
                        GradientStop { position: 1 ; color: control.pressed ? "#aaa" : "#ccc" }
                    }
                }
            }

        onClicked:
        {
            console.log('register clicked')
            main_page.source = 'register.qml'
            main_page_rect.x = 0
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
}
