#ifndef SOCKET_MANAGER_H
#define SOCKET_MANAGER_H

#include <QTcpSocket>
#include <QDataStream>
#include <QVector>
#include <QElapsedTimer>
#include <QRandomGenerator>
#include <QPair>

class SocketPair
{
public:
    explicit SocketPair()
    {
        input = new QTcpSocket();
        output = new QTcpSocket();
    }
    QTcpSocket *input;
    QTcpSocket *output;
};

class SocketManager : public QObject
{
    Q_OBJECT
public:
    explicit SocketManager(int number_sockets = 5, QObject *parent=nullptr);
    ~SocketManager(){}

    void start();

signals:
    void finished();

private slots:
    void error_handler(QAbstractSocket::SocketError error, int socket_number);

private:
    void setup_sockets();
    void _setup_error_handling(SocketPair socket_pair, int socket_number);

    void get_more_work(int socket_number);
    void do_work(QString work, SocketPair socket_pair, int socket_number);

    QVector<SocketPair> _sockets;
    QVector<QDataStream*> _data_streams;
    int _total_sockets;
    QRandomGenerator _random;
    QElapsedTimer _elasped_time;
};
#endif // SOCKET_MANAGER_H
