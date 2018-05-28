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

        gradient: Gradient {
            GradientStop {position: 0.0; color: "black"}
            GradientStop{position: 1.0; color: "blue"}
        }

        ParticleSystem {
            anchors.fill: parent
            ImageParticle {
                source: "qrc:///particleresources/glowdot.png"
                opacity: 0.25
            }
            Emitter {
                width: parent.width
                height: 150
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 3
                lifeSpan: 15000
                startTime: 15000
                emitRate: 5
                size: 24
                sizeVariation: 16
                acceleration: PointDirection{y: -6; xVariation: 2; yVariation: 2}
            }

            Wander {
                xVariance: 25
                pace: 25
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
