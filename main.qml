import QtQuick
import QtQuick.Controls.Fusion

Window {
    minimumWidth: 640
    minimumHeight: 480
    maximumWidth: 640
    maximumHeight: 480
    visible: true
    title: qsTr("Artchive")

    Text {
        id: current_directory_heading
        text: qsTr("Current Directory: ")
        x: 25
        y: 15
        font.bold: true
    }

    Text {
        id: current_directory
        text: designDirectory ? designDirectory.dir_path : "Loading..."
        anchors.top: current_directory_heading.top
        anchors.left: current_directory_heading.right
    }

    property string init_dir_path: ""

    TextField {
        id: design_path_id
        x: 25
        y: 50
        width: 200
        color: "#000"
        background: Rectangle {
            width: parent.width
            height: parent.height
            color: "#000"
            opacity: 0.1
            radius: 3
        }
        font.pointSize: 14
        placeholderText: qsTr("/design/path")
        renderType: Text.QtRendering
        onTextChanged: init_dir_path = text
    }

    Button {
        id: submit_button
        text: "Submit"
        x: 25
        y: 85
        topPadding: 5
        rightPadding: 15
        bottomPadding: 5
        leftPadding: 15
        background: Rectangle {
            width: parent.width
            height: parent.height
            color: '#26A4F4'
            opacity: submit_button.down ? 0.75 : (submit_button.hovered ? 0.5 : 0.25)
            radius: 3
        }
        onClicked: designDirectory.set_dir_path(init_dir_path)
    }

    Explorer {
        anchors.centerIn: parent
    }

    Image {
        id: icon_badge
        source: "qrc:/assets/icons/icon-chive.png"
        anchors {
            right: parent.right
            bottom: parent.bottom
        }
        width: 50
        height: 50
    }
}
