import QtQuick
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Artchive")

    Item {
        id: explorer
        width: 300
        height: 200

        ListModel {
            id: fileList

            ListElement {
                name: "design_one"
                extension: ".procreate"
            }

            ListElement {
                name: "design_one"
                extension: ".kra"
            }

            ListElement {
                name: "design_one"
                extension: ".fig"
            }
        }

        Component {
            id: fileListElement
            Text {
                text: name + extension
            }
        }

        ListView {
            anchors.fill: parent
            model: fileList
            delegate: fileListElement
            // Button: {
            //     id: button
            //     text: "Click to open popup"

            //     onClicked: {
            //         myPopup.open()
            //     }
            // }
        }
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
