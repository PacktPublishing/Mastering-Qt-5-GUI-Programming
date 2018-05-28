#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScopedPointer>
#include <QCamera>
#include <QCameraInfo>
#include <QAction>
#include <QCameraImageCapture>
#include <QCameraViewfinder>
#include <QPushButton>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void set_camera_action(QAction *camera_action);
    void set_camera(const QCameraInfo &camera_info);

private:
    void _setup_ui();
    void _setup_camera_devices();

    QScopedPointer<QCamera> _camera;
    QScopedPointer<QCameraImageCapture> _image_capture;
    QCameraViewfinder *_camera_view;
    QWidget *_central_widget;
    QPushButton *_take_image_button;
};

#endif // MAINWINDOW_H
