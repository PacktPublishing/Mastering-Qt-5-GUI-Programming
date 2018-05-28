#include "mainwindow.h"
#include <iostream>
#include <QWebEnginePage>
#include <QWebEngineProfile>
#include <QWebEngineScriptCollection>
#include <QWebEngineSettings>
#include <QUrl>
#include <QFile>
#include "websocketclientwrapper.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // create our browser
    _view = new QWebEngineView();
    // load a webpage
    _view->load(QUrl("qrc:///index.html"));
    // set our browser as the central widget in the MainWindow
    setCentralWidget(_view);

    if (!_start_websocket_server())
        qFatal("Failed to start web socket server on port 12345.");

    _webchannel = new QWebChannel();
    _webchannel->registerObject("interactive", &_interactive);

    // method connects relevant signal to the
    // `QWebChannel::connectTo` slot.
    _setup_webchannel_transport();
    _inject_javascript_into_page();

    // set font size large!
    _view->settings()->setFontSize(QWebEngineSettings::FontSize::MinimumFontSize, 26);
}

bool MainWindow::_start_websocket_server()
{
    // Note that the server is unsecured
    _websocket_server = new QWebSocketServer("Example Server", QWebSocketServer::NonSecureMode);
    // listen on port 12345
    return _websocket_server->listen(QHostAddress::LocalHost, 12345);
}

void MainWindow::_inject_javascript_into_page()
{
    QWebEnginePage *page = _view->page();
    QWebEngineScript custom_javascript = _get_custom_javascript();
    page->profile()->scripts()->insert(custom_javascript);
}

void MainWindow::_setup_webchannel_transport()
{
    // `WebSocketClientWrapper` wraps incoming WebSocket clients in QWebChannelAbstractTransport objects
    // See `handleNewConnection` method in `WebSocketClientWrapper` for relevant code
    _client_wrapper = new WebSocketClientWrapper(_websocket_server);
    // Note that every websocket client that connects to our websocket server gets
    // access to every published QObject.
    QObject::connect(_client_wrapper, &WebSocketClientWrapper::clientConnected,
                     _webchannel, &QWebChannel::connectTo);
}


QWebEngineScript MainWindow::_get_custom_javascript()
{
    // Read in `qwebchannel.js`
    QFile web_channel(":/qwebchannel.js");
    web_channel.open(QIODevice::ReadOnly);

    QByteArray javascript = web_channel.readAll();

    // Read in `script.js`
    QFile custom_javascript(":/script.js");
    custom_javascript.open((QIODevice::ReadOnly));

    // Note that the custom `script.js` is appended below `webchannel.js`
    javascript.append(custom_javascript.readAll());

    QWebEngineScript script;
    // Set our source code from `javascript` into our script
    script.setSourceCode(javascript);
    script.setName("qwebchannel.js");
    script.setRunsOnSubFrames(false);
    script.setWorldId(QWebEngineScript::MainWorld);
    script.setInjectionPoint(QWebEngineScript::DocumentCreation);
    return script;
}
