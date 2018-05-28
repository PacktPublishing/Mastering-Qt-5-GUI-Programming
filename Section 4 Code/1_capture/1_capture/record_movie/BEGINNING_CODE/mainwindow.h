#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaRecorder>
#include <QPushButton>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraInfo>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void record();
    void stop_recording();

private slots:
    void update_recorder_state(QMediaRecorder::State media_state);

private:

    void set_camera(const QCameraInfo &camera_info);
    void set_camera_action(QAction *camera_action);
    void _setup_camera_devices();
    void _setup_ui();

    QScopedPointer<QCamera> _camera;
    QCameraViewfinder *_camera_view;

    QWidget *_central_widget;

    QPushButton *_record_button;
    QPushButton *_stop_record_button;
};

#endif // MAINWINDOW_H
