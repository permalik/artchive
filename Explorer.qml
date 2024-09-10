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

        ListView {
           width: parent.width
           height: parent.height
           anchors.centerIn: parent
           spacing: 25
           topMargin: 10
           rightMargin: 10
           bottomMargin: 10
           leftMargin: 10
           model: ListModel {
               id: fileList
               Component.onCompleted: {
                   for (var i = 0; i < designFiles.items.length; i++) {
                       fileList.append({
                                           "name": designFiles.items[i],
                                           "color": designFiles.colors[i]
                                       })
                   }
               }
           }
           delegate: Item {
               TextInput {
                   text: model.name
                   readOnly: true
                   selectByMouse: true
                   color: model.color
               }
           }
        }
    }
}
