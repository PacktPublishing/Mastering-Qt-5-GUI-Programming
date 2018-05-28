#include "mainwindow.h"

#include <QActionGroup>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QVBoxLayout>


#include <iostream>


Q_DECLARE_METATYPE(QCameraInfo)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    _camera_view = new QCameraViewfinder();
    _record_button = new QPushButton("Record");
    _stop_record_button = new QPushButton("Stop Recording");

    _central_widget = new QWidget();
    setCentralWidget(_central_widget);

    _setup_ui();
    _setup_camera_devices();

    set_camera(QCameraInfo::defaultCamera());

    connect(_record_button, &QPushButton::clicked, this, &MainWindow::record);
    connect(_stop_record_button, &QPushButton::clicked, this, &MainWindow::stop_recording);
    connect(_media_recorder.data(), &QMediaRecorder::stateChanged, this, &MainWindow::update_recorder_state);

    if (_camera.data()->isCaptureModeSupported(QCamera::CaptureVideo))
        _camera.data()->setCaptureMode(QCamera::CaptureVideo);
    else
        qFatal("Capture Video not supported by this camera!");

}

void MainWindow::set_camera(const QCameraInfo &camera_info)
{
    _camera.reset(new QCamera(camera_info));
    _media_recorder.reset(new QMediaRecorder(_camera.data()));
    _camera.data()->setViewfinder(_camera_view);
    _camera.data()->start();
}

void MainWindow::record()
{
    _media_recorder.data()->record();
}

void MainWindow::stop_recording()
{
    _media_recorder.data()->stop();
}

MainWindow::~MainWindow()
{

}


void MainWindow::update_recorder_state(QMediaRecorder::State media_state)
{
    switch (media_state){
    case QMediaRecorder::RecordingState:
        _record_button->setEnabled(false);
        _stop_record_button->setEnabled(true);
        break;
    case QMediaRecorder::StoppedState:
        _record_button->setEnabled(true);
        _stop_record_button->setEnabled(false);
        break;
    }

}

void MainWindow::_setup_ui()
{
    QHBoxLayout *button_layout = new QHBoxLayout();

    button_layout->addWidget(_record_button);
    button_layout->addWidget(_stop_record_button);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addWidget(_camera_view);
    main_layout->addLayout(button_layout);

    _central_widget->setLayout(main_layout);
}

void MainWindow::_setup_camera_devices()
{
    QActionGroup *camera_group = new QActionGroup(this);
    const QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    QMenuBar* menu_bar = menuBar();
    QMenu *device_menu = menu_bar->addMenu("Devices");

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

void MainWindow::set_camera_action(QAction *camera_action)
{
    set_camera(qvariant_cast<QCameraInfo>(camera_action->data()));
}
