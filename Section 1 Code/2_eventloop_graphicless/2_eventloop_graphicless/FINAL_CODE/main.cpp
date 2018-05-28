#include <QCoreApplication>

#include "processmanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ProcessManager manager;
    manager.start();

    return a.exec();
}
