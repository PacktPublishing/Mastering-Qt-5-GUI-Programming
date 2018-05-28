#include "push_server.h"

PushServer::PushServer(int number_operations, QObject *parent):
    QObject(parent)
{
    qDebug() << "Start Push server";
    started = _server.listen(QHostAddress::LocalHost, 5000);

    for (int i = 0; i < number_operations; i++)
        _operations << QString::number(i);

    connect(&_server, &QTcpServer::newConnection, this, &PushServer::send_work);
}

void PushServer::send_work()
{
    QTcpSocket *client_connection = ;

    if (_operations.isEmpty())
    {
        // Need to give the client connection a second to write the last instruction as `write` is non-blocking
        QTimer::singleShot(50, [this](){emit finished();});
        return;
    }
    QString operation = ;

    qDebug() << "send work: " << operation;
}
