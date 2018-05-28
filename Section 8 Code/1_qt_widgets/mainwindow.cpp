#include "mainwindow.h"
#include "viridisdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    model = new PhotoModel();
    view = new QListView();
    setup_list_view_ui();

    view->setModel(model);

    connect(view, &QListView::clicked, this, &MainWindow::change_color);

    setCentralWidget(view);

}

void MainWindow::change_color(const QModelIndex &index)
{
    QVariant data = index.data(Qt::DecorationRole);
    QColor current_color = data.value<QColor>();
    QColor color = VirdisDialog::get_color(current_color);

    model->setData(index, color, Qt::DecorationRole);
}

MainWindow::~MainWindow()
{

}

void MainWindow::setup_list_view_ui()
{
    view->setIconSize(QSize(90, 90));
    view->setViewMode(QListView::IconMode);
    view->setResizeMode(QListView::Adjust);
}
