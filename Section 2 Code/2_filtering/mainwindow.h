#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColor>
#include <QMainWindow>
#include <QListView>
#include <QToolButton>

#include "photomodel.h"
#include "picturefilter.h"
#include "viridisdialog.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void set_minimum();
    void set_maximum();

private:
    void setup_list_view_ui();
    void setup_tool_buttons_ui();
    void update_button_icon(QColor color, QToolButton* button);

    QToolButton *min_button;
    QToolButton *max_button;

    QListView *list_view;
    PhotoModel *photo_model;

    PictureFilter *picture_filter;

    QColor color_min;
    QColor color_max;
};

#endif // MAINWINDOW_H
