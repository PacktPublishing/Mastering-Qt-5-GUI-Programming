#include "interactor.h"


void Interactor::call_me_from_website()
{
    qDebug() << "`call_me_from_website` called using JavaScript!";
    qDebug() << "    ...see `script.js` for JavaScript code that does this";
}

QString Interactor::call_me_returns_string()
{
    return "This is a neat string";
}

void Interactor::launch_new_window()
{
    _message_box = new QMessageBox();
    _message_box->setText("`Open Dialogue in GUI` button pushed on website, triggering GUI changes");
    _message_box->exec();
}

void Interactor::set_string(QString new_string)
{
    _who_changed_this_string = new_string;
    emit string_changed();
}

QString Interactor::get_string()
{
    return _who_changed_this_string;
}
