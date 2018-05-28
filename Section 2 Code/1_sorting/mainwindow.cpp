#include "mainwindow.h"
#include "sortproxymodel.h"

#include <QSortFilterProxyModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // instance of the custom type `PhotoItemModel`
    model = new PhotoItemModel();

    list_view = new QListView();
    list_view->setModel(model);
    setup_list_view_ui();

    table_view = new QTableView();
    table_view->setModel(model);
    setup_table_view_ui();

    central_widget = new QTabWidget();
    central_widget->addTab(list_view, "Proxy Model Example");
    central_widget->addTab(table_view, "Programtic Sorting Example");

    setCentralWidget(central_widget);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setup_list_view_ui()
{
    list_view->setIconSize(QSize(90, 90));
    list_view->setViewMode(QListView::IconMode);
    list_view->setResizeMode(QListView::Adjust);
}

void MainWindow::setup_table_view_ui()
{
    table_view->setIconSize(QSize(100, 100));
    // table_view->setSortingEnabled(true);
}
