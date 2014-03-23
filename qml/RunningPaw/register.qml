import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1

Rectangle {
    id: register
    width: 480
    height: 640

    color: "white"

    property int displayMargin : parent.width / 40;
    property int txtPointSize : 15;

    Row{
        id: register_group_box
        anchors.centerIn: parent

        Column{
            Text {
                id: txt_register_username

                text: qsTr("Username")
                font.pointSize: txtPointSize
                color: "black"
            }

            Text{
                text: " "
                font.pointSize: 5
            }

            Text {
                id: txt_register_password

                text: qsTr("Password")
                font.pointSize: txtPointSize
                color: "black"
            }
        }

        Column{
            TextField{
                id : input_register_username
                font.pointSize: txtPointSize

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

            Text{
                text: " "
                font.pointSize: 5
            }

            TextField{
                id : input_register_password
                anchors.left: input_register_username.left

                font.pointSize: txtPointSize
                echoMode: TextInput.Password

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
        }
    }

    Button{
        id: btn_register_ok
        text: "Register OK"

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: register_group_box.bottom
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
            console.log('register_ok clicked')
            main_page.source = 'main.qml'
            main_page_rect.x = 0
        }
    }

}
