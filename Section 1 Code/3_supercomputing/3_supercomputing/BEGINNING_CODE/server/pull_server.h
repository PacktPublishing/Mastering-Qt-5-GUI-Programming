#ifndef PULL_SERVER_H
#define PULL_SERVER_H

#include <iostream>
#include <QStringList>

#include <QTcpServer>
#include <QDataStream>
#include <QTcpSocket>

class PullServer : public QObject
{
public:
    explicit PullServer(QObject *parent=nullptr) : QObject(parent)
    {

        bool sucess = _server.listen(QHostAddress::LocalHost, 5001);
        connect(&_server, &QTcpServer::newConnection, this, &PullServer::recieve_work);
    }

private slots:
    void recieve_work()
    {
        QTcpSocket *client_connection = _server.nextPendingConnection();
        connect(client_connection, &QAbstractSocket::disconnected, client_connection, &QObject::deleteLater);
        QDataStream in;
        in.setDevice(client_connection);

        in.startTransaction();

        QString result;
        in >> result;

        if (in.commitTransaction())
            return;

        if (!result.isEmpty())
            std::cout << "-> Result is: " << result.toStdString() << std::endl;

        connect(client_connection, &QAbstractSocket::disconnected, client_connection, &QObject::deleteLater);
    }
private:
    QTcpServer _server;
};

#endif // PULL_SERVER_H
