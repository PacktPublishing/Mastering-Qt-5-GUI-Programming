#ifndef PHOTOITEMMODEL_H
#define PHOTOITEMMODEL_H

#include <QIcon>
#include <QVariant>
#include <QStandardItem>
#include <QStandardItemModel>
#include "luminosity_calc.h"

class PhotoItemModel : public QStandardItemModel
{
public:
    PhotoItemModel(QObject *parent=0):
        QStandardItemModel(parent)
    {
        QIcon last_icon(QString(":/pics/99.png"));

        for (int i = 0; i < 100; i++)
        {
            QString filepath(":/pics/" + QString::number(i) + ".png");
            QIcon icon(filepath);

            QStandardItem *item = new QStandardItem();
            item->setIcon(icon);

            setItem(i, 0, item);

            // Second row
            QStandardItem *second_item = new QStandardItem();
            second_item->setIcon(last_icon);

            setItem(i, 1, second_item);

            last_icon = icon;
        }

    }
};



#endif // PHOTOITEMMODEL_H
