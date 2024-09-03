import QtQuick

Item {
    id: explorer

    Rectangle {
        id: explorerContainer
        width: 300
        height: 200
        border.width: 1
        border.color: "#E5E5E5"
        radius: 5
        anchors.centerIn: parent

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
            anchors.centerIn: parent
            width: parent.width
            height: parent.height
            spacing: 5
            topMargin: 10
            rightMargin: 10
            bottomMargin: 10
            leftMargin: 10
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
}
