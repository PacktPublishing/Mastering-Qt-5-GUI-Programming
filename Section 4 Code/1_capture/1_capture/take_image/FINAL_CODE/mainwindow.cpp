#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QActionGroup>
#include <QVBoxLayout>

Q_DECLARE_METATYPE(QCameraInfo)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    _camera_view = new QCameraViewfinder();
    _take_image_button = new QPushButton("Take Image");

    _central_widget = new QWidget();
    setCentralWidget(_central_widget);

    _setup_ui();
    _setup_camera_devices();
    set_camera(QCameraInfo::defaultCamera());

    connect(_take_image_button,
                 &QPushButton::clicked,
                 [this]{_image_capture.data()->capture();});
}

void MainWindow::_setup_ui()
{
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(_camera_view);
    layout->addWidget(_take_image_button);
    _central_widget->setLayout(layout);
}

void MainWindow::_setup_camera_devices()
{
    const QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    QMenuBar *menu_bar = menuBar();
    QMenu *device_menu = menu_bar->addMenu("Devices");

    QActionGroup *camera_group = new QActionGroup(this);

    for (const QCameraInfo &camera_info: cameras)
    {
        QAction *camera_action = new QAction(camera_info.description(), camera_group);
        camera_action->setCheckable(true);
        camera_action->setData(QVariant::fromValue(camera_info));
        if (camera_info == QCameraInfo::defaultCamera())
            camera_action->setChecked(true);
        device_menu->addAction(camera_action);
    }

    connect(camera_group, &QActionGroup::triggered, this, &MainWindow::set_camera_action);
}

MainWindow::~MainWindow()
{

}



void MainWindow::set_camera_action(QAction *camera_action)
{
    set_camera(qvariant_cast<QCameraInfo>(camera_action->data()));
}

void MainWindow::set_camera(const QCameraInfo &camera_info)
{
    _camera.reset(new QCamera(camera_info));
    _image_capture.reset(new QCameraImageCapture(_camera.data()));

    _camera.data()->setCaptureMode(QCamera::CaptureStillImage);
    _camera.data()->setViewfinder(_camera_view);
    _camera.data()->start();
}
