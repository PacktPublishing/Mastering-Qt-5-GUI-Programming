#include "mainwindow.h"

#include <QVBoxLayout>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    web_view = new QWebEngineView();
    central_widget = new QWidget();
    edit_bar = new QLineEdit();
    setup_central_widget_ui();

    QString temp("www.wikipedia.org");
    edit_bar->setText(temp);

    web_view->load(QUrl(temp));
    connect(edit_bar, &QLineEdit::editingFinished, this, &MainWindow::set_url);

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
    QString url_string = edit_bar->text();
    web_view->load(QUrl::fromUserInput(url_string));
}

MainWindow::~MainWindow()
{

}
