import QtQuick

Item {
    id: explorer
    width: 300
    height: 200
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
