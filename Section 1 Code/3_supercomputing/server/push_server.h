#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include <iostream>
#include <QStringList>

#include <QTimer>
#include <QDebug>
#include <QTcpServer>
#include <QDataStream>
#include <QTcpSocket>


class PushServer : public QObject
{
    Q_OBJECT
public:
    explicit PushServer(int number_operations = 101,  QObject *parent=nullptr);

private slots:
    void send_work();

signals:
    void finished();

private:
    QTcpServer _server;
    QStringList _operations;

public:
    bool started;
};
#endif // SERVERMANAGER_H
