import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.2


Window {
    id: window
    visible: true
    width: 640
    height: 480

    Rectangle {
        id: blue_ball
        width: 50
        height: 50
        radius: 50
        property int min_height: 2 * window.height / 5
        property int max_height: window.height / 5
        anchors.horizontalCenter: parent.horizontalCenter
        y: min_height
        color: "blue"

        SequentialAnimation on y {
            loops: Animation.Infinite
            NumberAnimation {
                from: blue_ball.min_height
                to: blue_ball.max_height
                easing.type: Easing.OutExpo
                duration: 300
            }
            NumberAnimation {
                from: blue_ball.max_height
                to: blue_ball.min_height
                duration: 1000
                easing.type: Easing.OutBounce
            }

            PauseAnimation {
                duration: 500
            }
        }
    }

    Timer {
        property bool first: true
        interval: 1500
        onTriggered: {
            if (go_button.wiggle_value == 0)
                go_button.wiggle_value = 10;
            else
                go_button.wiggle_value = 0

             // reset interval to be longer so this isn't as annoying
            if (first)
                interval = 3000;

        }
        running: true
        repeat: true
    }

    Button {
        id: go_button
        text: "Launch App!"
        anchors.horizontalCenter: parent.horizontalCenter
        y: 2 * window.height / 3
        property int wiggle_value: 0

        transform: Rotation {
            origin.x: go_button.width /2
            origin.y: go_button.height / 2
            angle: go_button.wiggle_value

            Behavior on angle {
                SequentialAnimation {
                    loops: 2
                    NumberAnimation {
                        duration: 60
                    }
                    NumberAnimation {
                        to: -10
                        duration: 120
                    }
                    NumberAnimation {
                        to: 0
                        duration: 60
                    }
                }
            }
        }
    }


}
