import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.2
import QtQuick.Particles 2.0


Window {
    id: window
    visible: true
    width: 640
    height: 480

    // NOTE: Added in rectangle from last example
    Rectangle {
        anchors.fill: parent


        Rectangle {
            id: my_rect
            property int max_height: window.height / 5
            property int min_height: 2 * window.height / 5
            radius: 50
            anchors.horizontalCenter: parent.horizontalCenter
            color: "blue"
            width: 50
            height: 50
            y: min_height

            SequentialAnimation on y {
                id: my_animation
                loops: 3

                NumberAnimation {
                    from: my_rect.min_height
                    to: my_rect.max_height
                    easing.type: Easing.OutExpo
                    duration: 300
                }
                NumberAnimation {
                    from: my_rect.max_height
                    to: my_rect.min_height
                    easing.type: Easing.OutBounce;
                    duration: 1000
                }

                PauseAnimation {
                    duration: 500
                }
            }
        }

        Button {
            // anchors.horizontalCenter: parent.horizontalCenter
            id: ready_button
            y: 2* window.height / 3
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Launch App"

            property int wiggle_value: 0

            Timer {
                property bool first: true
                interval: 1500
                onTriggered: {
                    if (ready_button.wiggle_value == 0)
                        ready_button.wiggle_value = 10;
                    else
                        ready_button.wiggle_value = 0

                    if (first)
                        interval = 3000;

                }
                running: true
                repeat: true
            }

            transform: Rotation {
                origin.x: ready_button.width/2
                origin.y: ready_button.height/2
                angle: ready_button.wiggle_value
                Behavior on angle {
                    SequentialAnimation {
                        NumberAnimation{
                            duration: 60
                        }
                        NumberAnimation{
                            // NOTE: Must use real numbers here
                            // Cannot use `ready_button.wiggle_value`
                            to: -10
                            duration: 120
                        }
                        NumberAnimation{
                            to: 0
                            duration: 60
                        }
                        loops: 2
                    }
                }
            }
        }
    }
}
