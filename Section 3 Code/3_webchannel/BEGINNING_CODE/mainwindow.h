#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QWebChannel>
#include <QWebEngineScript>
#include <QWebSocketServer>

#include "websocketclientwrapper.h"
#include "interactor.h"



class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    bool _start_websocket_server();
    void _setup_webchannel_transport();
    QWebEngineScript _get_custom_javascript();
    void _inject_javascript_into_page();

private:
    // Our Web Browser
    QWebEngineView *_view;

    // The Web Channel
    QWebChannel *_webchannel;

    // Web Socket Server
    QWebSocketServer *_websocket_server;

    // WebSocket to QWebChannel interface (code not covered)
    WebSocketClientWrapper *_client_wrapper;

    // Object to publish over QWebChannel
    Interactor _interactive;
};

#endif // MAINWINDOW_H
