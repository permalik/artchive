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

    Image {
        source: "qrc:/assets/icons/icon-chive.png"
        anchors {
            right: parent.right
            bottom: parent.bottom
        }
        width: 50
        height: 50
    }
}
