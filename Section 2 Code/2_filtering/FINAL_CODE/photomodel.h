#ifndef PHOTOITEMMODEL_H
#define PHOTOITEMMODEL_H

#include <QIcon>
#include <QImage>
#include <QObject>
#include <QVariant>
#include <QStandardItem>
#include <QStandardItemModel>


class PhotoModel : public QStandardItemModel
{
public:
    PhotoModel(QObject *parent=0):
        QStandardItemModel(parent)
    {
        // NOTE: This block of text loads in our pictures
        for (int i = 0; i < 100; i++)
        {
            // Create Icon
            QString filepath(":/pics/" + QString::number(i) + ".png");
            QIcon icon(filepath);

            // Create Item & Set Icon
            QStandardItem *item = new QStandardItem();
            item->setIcon(icon);

            // Set Item in model
            this->setItem(i, 0, item);
        }

    }
};

#endif // PHOTOITEMMODEL_H
