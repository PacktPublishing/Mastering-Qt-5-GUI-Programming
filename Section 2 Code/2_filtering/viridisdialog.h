#ifndef VIRDISDIALOG_H
#define VIRDISDIALOG_H

#include <QDialog>
#include "colorpicker.h"


class VirdisDialog : public QDialog
{
public:
    VirdisDialog(QColor color, QWidget *parent=0);
    static QColor get_color(QColor color, QWidget* parent=0, const QString &title=QString());
private:
    QColor get_current_color();
    ColorPicker *picker;
};

#endif // VIRDISDIALOG_H
