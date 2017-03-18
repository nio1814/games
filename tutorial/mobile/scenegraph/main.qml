import QtQuick 2.3
import SceneGraph 1.0

Item {
    visible: true

    width: 320
    height: 480

    MouseArea {
        anchors.fill: parent
        onClicked: {
//            Qt.quit();
        }
    }

    Text {
        text: qsTr("App")
        anchors.centerIn: parent
    }

    Squircle
    {
        SequentialAnimation on t
        {
            NumberAnimation
            {
                to: 1
                duration: 2500
                easing.type: Easing.InOutQuad
            }
            NumberAnimation
            {
                to: 0
                duration: 2500
                easing.type: Easing.OutInCirc
            }

            loops: Animation.Infinite
            running: true
        }
    }
}
