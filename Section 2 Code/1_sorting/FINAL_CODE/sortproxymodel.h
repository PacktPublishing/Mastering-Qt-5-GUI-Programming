#ifndef PICTURESORT_H
#define PICTURESORT_H

#include <QIcon>
#include <QSortFilterProxyModel>
#include "luminosity_calc.h"


class SortProxyModel: public QSortFilterProxyModel
{
protected:
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
    {
        QVariant left_data = sourceModel()->data(source_left, Qt::DecorationRole);
        QVariant right_data = sourceModel()->data(source_right, Qt::DecorationRole);

        QIcon left_icon = left_data.value<QIcon>();
        QIcon right_icon = right_data.value<QIcon>();

        return luminosity_less_than(left_icon, right_icon);
    }
};

#endif // PICTURESORT_H
