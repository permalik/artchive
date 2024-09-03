import QtQuick
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Artchive")

    Explorer {
        anchors.centerIn: parent
    }

    // Popup {
    //     id: myPopup
    //     width: 150
    //     height: 75
    //     closePolicy: "CloseOnEscape"
    //     anchors.centerIn: parent

    //     Column {
    //         spacing: 10

    //         Button {
    //             text: "close"
    //             width: 100
    //             onClicked: {
    //                 myPopup.close()
    //             }
    //         }
    //     }
    // }
}
