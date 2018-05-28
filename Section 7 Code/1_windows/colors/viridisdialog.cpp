#include "viridisdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

VirdisDialog::VirdisDialog(QColor color, QWidget *parent) :
    QDialog(parent)
{
    QVBoxLayout *main_layout = new QVBoxLayout();

    picker = new ColorPicker(color);
    main_layout->addWidget(picker);

    QHBoxLayout *box_layout = new QHBoxLayout();

    QPushButton *ok =  new QPushButton("Ok");
    box_layout->addWidget(ok);
    connect(ok, &QPushButton::clicked, this, &VirdisDialog::accept);

    main_layout->addLayout(box_layout);
    setLayout(main_layout);
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
