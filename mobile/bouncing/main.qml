import QtQuick 2.3
import Bouncing 1.0

Item {
    visible: true

    MouseArea {
        anchors.fill: parent
        onClicked: {
//            Qt.quit();
        }
    }

    Text {
        id: label
        wrapMode: Text.WordWrap
        text: "This app is rendered with raw OpenGL using the 'beforeRender' signal in QQuickWindow"
//        anchors.centerIn: parent
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.margins: 20
    }

//    Scene {

//    }
}
