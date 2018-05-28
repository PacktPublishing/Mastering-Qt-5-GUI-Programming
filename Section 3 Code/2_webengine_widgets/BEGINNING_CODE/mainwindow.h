#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QLineEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void set_url();

private:
    void setup_central_widget_ui();

    QWidget *central_widget;
    QWebEngineView *web_view;
    QLineEdit* edit_bar;
};

#endif // MAINWINDOW_H
