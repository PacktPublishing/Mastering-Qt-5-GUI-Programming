#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <QObject>
#include <QVector>
#include <QProcess>
#include <QTimer>

class ProcessManager : public QObject
{
    Q_OBJECT
public:
    explicit ProcessManager(int max_processes=5, QObject *parent = nullptr);
    void start();

signals:

private slots:
    void start_process();
    void start_process(QString name);
    void process_finished(int exit_code, QProcess::ExitStatus status, QProcess *process, QString process_name);
    void error_handler(QProcess::ProcessError error, QProcess *process, QString process_name);
    void kill_process(QProcess* process, QString name);

private:
    void setup_connections(QProcess *process, QString process_name);

    QTimer *_timer;
    int _num_process;
    int _max_processes;
    QVector<QProcess*> _processes;

    QProcess *_sacrifice;
};

#endif // PROCESSMANAGER_H
