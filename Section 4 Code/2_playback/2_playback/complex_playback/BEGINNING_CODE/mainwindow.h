#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QPushButton>
#include "videowidget.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void trigger_media_file_dialog();
    void update_button_state(QMediaPlayer::State state);

private:
    void _setup_ui();

    QMediaPlayer * _media_player;
    QMediaPlaylist *_media_playlist;
    VideoWidget * _video_widget;
    QWidget *_central_widget;

    QPushButton *_play_button;
    QPushButton *_pause_button;
    QPushButton *_stop_button;

    QPushButton *_next_video;
    QPushButton *_previous_video;
    QAction *_open_file;
};

#endif // MAINWINDOW_H
