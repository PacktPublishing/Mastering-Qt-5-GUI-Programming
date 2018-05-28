#include "mainwindow.h"

#include <QColor>
#include <QColorDialog>
#include <QVBoxLayout>
#include <QHeaderView>

#include "huegenerator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    central_widget = new QWidget();
    new_color_button = new QPushButton("New Color");

    view = new QTreeView();
    model = new PictureModel();

    view->setModel(model);

    setup_central_widget_ui();
    setup_tree_view_ui();

    connect(new_color_button, &QPushButton::clicked, this, &MainWindow::get_color);
    connect(view, &QTreeView::expanded, this, &MainWindow::resize_columns);

    setCentralWidget(central_widget);
}

MainWindow::~MainWindow()
{

}

void MainWindow::get_color()
{
    QColor new_color = QColorDialog::getColor();
    ColorVec colors = generate_hues(new_color);
    model->add_colors(colors);
}

void MainWindow::setup_tree_view_ui()
{
    view->setIconSize(QSize(50, 50));
    view->setUniformRowHeights(true);
    view->header()->hide();
}

void MainWindow::resize_columns(QModelIndex index)
{
    for (int i=0; i < 12; i++)
        view->resizeColumnToContents(i);
}

void MainWindow::setup_central_widget_ui()
{
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(view);
    layout->addWidget(new_color_button);

    central_widget->setLayout(layout);
}
