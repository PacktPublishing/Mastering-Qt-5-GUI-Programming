import QtQuick 2.9
import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0
import Qt3D.Extras 2.0

Entity {
    Camera {
        id: camera
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 45
        aspectRatio: 16/9
        nearPlane: 0.1
        farPlane: 1000
        position: Qt.vector3d(0.0, 0.0, -40.0)
        upVector: Qt.vector3d(0.0, 1.0, 0.0)
        viewCenter: Qt.vector3d(0.0, 0.0, 0.0)
    }

    components: [
        RenderSettings {
            activeFrameGraph: ForwardRenderer {
                camera: camera
                clearColor: Qt.rgba(0, 0.5, 1, 1)
            }
        },
        InputSettings {}
    ]

    FirstPersonCameraController { camera: camera }

    SphereMesh {
        id: mesh
        radius: 3
        slices: 30
        rings: 30
    }

    PhongMaterial {
        id: material
        diffuse: Qt.rgba(1, 0.2, 0, 1)
    }

    Entity {
        components: [mesh, material]
    }

    Transform {
        id: transform
        property real user_angle: 0.0
        matrix: {
            var m = Qt.matrix4x4();
            m.rotate(user_angle, Qt.vector3d(0, 1, 0));
            m.translate(Qt.vector3d(20, 0, 0));
            return m;
        }
    }

    NumberAnimation {
        target: transform
        property: "user_angle"
        duration: 10000
        from: 0
        to: 360
        loops: Animation.Infinite
        running: true
    }

    Entity {
        components: [mesh, material, transform]
    }


}
