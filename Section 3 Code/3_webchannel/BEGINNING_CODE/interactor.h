#ifndef INTERACTOR_H
#define INTERACTOR_H

#include <QMessageBox>
#include <QDebug>

class Interactor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString who_changed_this_string  READ get_string WRITE set_string NOTIFY string_changed)
public:
    explicit Interactor(QObject *parent = nullptr) : QObject(parent), _who_changed_this_string("C++ Application"){}

public slots:
    void call_me_from_website();
    void launch_new_window();
    QString call_me_returns_string();

signals:
    void string_changed();

public:
    void set_string(QString new_string);
    QString get_string();

private:
    QMessageBox *_message_box;
    QString _who_changed_this_string;
};

#endif // INTERACTOR_H
