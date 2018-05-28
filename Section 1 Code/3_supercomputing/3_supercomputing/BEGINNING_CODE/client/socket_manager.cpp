#include "socket_manager.h"

#include <iostream>
#include <QTimer>
#include <QHostAddress>


SocketManager::SocketManager(int number_sockets,
                                                       QObject *parent) :
    QObject(parent),
    _total_sockets(number_sockets)
    {
        setup_sockets();
    }


void SocketManager::setup_sockets()
{
    for (int sock_num =0; sock_num < _total_sockets; sock_num++)
    {
        SocketPair socket_pair;
        _sockets.append(socket_pair);
        _setup_error_handling(socket_pair, sock_num);

        socket_pair.output->connectToHost(QHostAddress::LocalHost, 5001);

        QDataStream *data_stream = new QDataStream();
        _data_streams.append(data_stream);

        data_stream->setDevice(socket_pair.input);

        connect(socket_pair.input, &QIODevice::readyRead, [this, sock_num, data_stream, socket_pair](){

        });
    }
}


void SocketManager::do_work(QString work, SocketPair socket_pair, int socket_number)
{
    // NOTE: in real code, work calculations would happen before we
    // compress the data again.

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << work;


    if (socket_pair.output->state() == QAbstractSocket::ConnectedState)
    {
    }

    std::cout << "Did work: " << work.toStdString() << " with socket # " << socket_number << std::endl;


    int simulated_work_time = _random.bounded(500);
    QTimer::singleShot(simulated_work_time, [this, socket_number](){get_more_work(socket_number);});

    if (work.toInt() == 100)
    {
        std::cout << "Time elasped: " << (float) _elasped_time.elapsed() / 1000 << " seconds" << std::endl;
        emit finished();
    }
}


void SocketManager::start()
{
    std::cout << "Start" << std::endl << std::endl;
    _elasped_time.start();
    for (int i = 0; i < _total_sockets; i++)
    {
        SocketPair socket_pair = _sockets[i];
        socket_pair.input->connectToHost(QHostAddress::LocalHost, 5000);
    }
}

void SocketManager::get_more_work(int socket_number)
{
    QTcpSocket *socket = _sockets[socket_number].input;
    socket->abort();
    socket->connectToHost(QHostAddress::LocalHost, 5000);
}

void SocketManager::error_handler(QAbstractSocket::SocketError error, int socket_number)
{
    if (error == QAbstractSocket::ConnectionRefusedError)
    {
        QTimer::singleShot(1000, [this, socket_number](){get_more_work(socket_number);});
        if (_random.bounded(_total_sockets) == 0)
            std::cout << "No host found, is the server running?" << std::endl;
    }
}

void SocketManager::_setup_error_handling(SocketPair socket_pair, int socket_number)
{
    connect(socket_pair.input,
                  QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
                  [this, socket_number](QAbstractSocket::SocketError error){error_handler(error, socket_number);});
}
