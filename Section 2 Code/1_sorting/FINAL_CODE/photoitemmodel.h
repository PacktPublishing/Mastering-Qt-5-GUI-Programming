#ifndef PHOTOITEMMODEL_H
#define PHOTOITEMMODEL_H

#include <QIcon>
#include <QVariant>
#include <QStandardItem>
#include <QStandardItemModel>
#include "luminosity_calc.h"

class PhotoItem : public QStandardItem
{
public:
    bool operator <(const QStandardItem& other) const
    {
        QVariant left_data = data(Qt::DecorationRole);
        QVariant right_data = other.data(Qt::DecorationRole);

        QIcon left_icon = left_data.value<QIcon>();
        QIcon right_icon = right_data.value<QIcon>();

        return luminosity_less_than(left_icon, right_icon);
    }
};

class PhotoItemModel : public QStandardItemModel
{
public:
    PhotoItemModel(QObject *parent=0):
        QStandardItemModel(parent)
    {
        QIcon last_icon(QString(":/pics/99.png"));

        for (int i = 0; i < 100; i++)
        {
            // Create Icon
            QString filepath(":/pics/" + QString::number(i) + ".png");
            QIcon icon(filepath);

            // Create Item & Set Icon
            PhotoItem *item = new PhotoItem();
            item->setIcon(icon);

            // Set Item in model
            setItem(i, 0, item);

            // Second column
            PhotoItem *second_item = new PhotoItem();
            second_item->setIcon(last_icon);

            setItem(i, 1, second_item);

            last_icon = icon;
        }

    }
};



#endif // PHOTOITEMMODEL_H
