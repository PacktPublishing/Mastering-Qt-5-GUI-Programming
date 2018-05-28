#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QCamera>
#include <QCameraInfo>
#include "videowidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    void set_camera(const QCameraInfo &camera_info);
    void set_camera_action(QAction *camera_action);
    void _setup_camera_devices();

    QScopedPointer<QCamera> _camera;

    QWidget *_central_widget;

    QPushButton *_record_button;
    QPushButton *_stop_record_button;
    VideoWidget *_video_widget;
};

#endif // MAINWINDOW_H
