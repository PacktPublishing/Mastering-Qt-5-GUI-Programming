#include "viridisdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

VirdisDialog::VirdisDialog(QColor color, QWidget *parent) :
    QDialog(parent)
{
    picker = new ColorPicker(color);
    QPushButton *ok =  new QPushButton("Ok");

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(picker);
    layout->addWidget(ok);

    connect(ok, &QPushButton::clicked, this, &VirdisDialog::accept);

    setLayout(layout);
}

QColor VirdisDialog::get_current_color()
{
    return picker->current_color;
}

QColor VirdisDialog::get_color(QColor color, QWidget *parent, const QString &title)
{
    VirdisDialog dialog(color, parent);
    if (!title.isEmpty())
        dialog.setWindowTitle(title);
    dialog.exec();
    return dialog.get_current_color();
}
