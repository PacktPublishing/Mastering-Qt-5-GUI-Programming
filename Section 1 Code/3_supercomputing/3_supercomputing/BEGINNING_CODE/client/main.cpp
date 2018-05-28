#include <QCoreApplication>
#include <QObject>
#include "socket_manager.h"



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int number_workers = 5;

    SocketManager manager(number_workers);
    QObject::connect(&manager, &SocketManager::finished, &a, &QCoreApplication::quit);
    manager.start();

    return a.exec();
}
