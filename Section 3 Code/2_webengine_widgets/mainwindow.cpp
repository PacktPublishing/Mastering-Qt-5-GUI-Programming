#include "mainwindow.h"

#include <QVBoxLayout>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    web_view = ;
    central_widget = ;
    edit_bar = ;
    setup_central_widget_ui();

    setCentralWidget(central_widget);
}

void MainWindow::setup_central_widget_ui()
{
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(edit_bar);
    layout->addWidget(web_view);

    central_widget->setLayout(layout);
}

void MainWindow::set_url()
{
}

MainWindow::~MainWindow()
{

}
