#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QActionGroup>
#include <QVBoxLayout>

Q_DECLARE_METATYPE(QCameraInfo)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    _camera_view = ;
    _take_image_button = new QPushButton("Take Image");

    _central_widget = new QWidget();
    setCentralWidget(_central_widget);

    _setup_ui();
    _setup_camera_devices();

    connect(_take_image_button,
                 &QPushButton::clicked,);
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
    const QList<QCameraInfo> cameras = ;
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
    _camera.data()->start();
}
