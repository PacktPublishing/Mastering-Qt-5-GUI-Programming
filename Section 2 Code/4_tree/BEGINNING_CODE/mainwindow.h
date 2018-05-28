#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>
#include <QPushButton>
#include "picturemodel.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void get_color();

private:
    void resize_columns(QModelIndex index);
    void setup_tree_view_ui();
    void setup_central_widget_ui();

    QTreeView *view;
    PictureModel *model;
    QWidget *central_widget;
    QPushButton *new_color_button;
};

#endif // MAINWINDOW_H
