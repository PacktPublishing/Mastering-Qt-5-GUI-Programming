#include "processmanager.h"
#include <QDebug>


ProcessManager::ProcessManager(int max_processes, QObject *parent) :
    QObject(parent),
    _num_process(0),
    _max_processes(max_processes),
    _sacrifice(new QProcess(this))
{
    _timer = new QTimer();
    _timer->setInterval(1500);

    connect(_timer, &QTimer::timeout, this, QOverload<>::of(&ProcessManager::start_process));

    // simulates a kill process signal from the network
    QTimer::singleShot(8000, [this](){kill_process(_sacrifice, "Sacrifical Process");});
}

void ProcessManager::start_process(QString name)
{
    qDebug() << "starting process # " << _num_process << " process: " << name;

    QProcess *process = new QProcess(this);
    _processes.append(process);
    process->start(name);

    setup_connections(process, name);

    _num_process += 1;

    if (_num_process == _max_processes)
    {
        qDebug() << "max processes reached! Stopping timer!";
        _timer->stop();
    }
}

void ProcessManager::setup_connections(QProcess *process, QString process_name)
{
    // TODO: Connect the `finished` and `errorOccured` signals up
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            [process, process_name, this](int exit_code, QProcess::ExitStatus status){this->process_finished(exit_code, status, process, process_name);});

    connect(process, &QProcess::errorOccurred, [process, process_name, this](QProcess::ProcessError error){this->error_handler(error, process, process_name);});



    // NOTE: Unused process signals:
    //       started, stateChanged, readyReadStandard[Error/Output]

}

void ProcessManager::process_finished(int exit_code, QProcess::ExitStatus status, QProcess* process, QString process_name)
{
    if (status == QProcess::NormalExit)
    {
        qDebug() << "normal exit for process: " << process_name;
        _processes.removeOne(process);
    }
    else if (status == QProcess::CrashExit)
    {
        qWarning() << "Process crashed! Process: " << process_name;
        qDebug() << "Exit code: " << exit_code;
        process->start(process_name);
    }
}

void ProcessManager::kill_process(QProcess* process, QString name)
{
    qDebug() << "Killed process: " << name;

#ifdef Q_OS_WIN
    // Console applications on Windows that do not run an event loop,
    // or whose event loop does not handle the WM_CLOSE message, can only be terminated by calling kill
    process->kill();
#else
    // Nice version
    process->terminate();
    // process->kill();
#endif

    // Not nice version

    return;
}

void ProcessManager::error_handler(QProcess::ProcessError error, QProcess *process, QString process_name)
{
    qDebug() << "Error!";

    switch (error) {
    case QProcess::Crashed:

        break;

    case QProcess::FailedToStart:

        break;

    case QProcess::Timedout:

        break;

    case QProcess::WriteError:

        break;

    case QProcess::ReadError:

        break;

    case QProcess::UnknownError:

        break;
    }
}

void ProcessManager::start()
{
    qDebug() << "Starting!";
    _timer->start();
    _sacrifice->start();
}

void ProcessManager::start_process()
{
    start_process(QString());
}
