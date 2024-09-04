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

    property string init_dir_path: ""

    TextField {
        id: design_path_id
        x: 320
        y: 50
        color: "#000"
        font.pointSize: 14
        placeholderText: "/design/path"
        renderType: Text.QtRendering
        onTextChanged: init_dir_path = text
    }

    Button {
        text: "Submit"
        x: 350
        y: 100
        onClicked: designDirectory.set_dir_path(init_dir_path)
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
