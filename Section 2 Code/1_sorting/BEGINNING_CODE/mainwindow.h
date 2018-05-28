#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QListView>
#include <QTableView>
#include "photoitemmodel.h"
#include "sortproxymodel.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void setup_list_view_ui();
    void setup_table_view_ui();

    // The two main views, a QListView and QTableView
    QListView *list_view;
    QTableView *table_view;

    // Our model
    PhotoItemModel *model;

    QTabWidget *central_widget;
    SortProxyModel *sort_proxy_model;

};

#endif // MAINWINDOW_H
