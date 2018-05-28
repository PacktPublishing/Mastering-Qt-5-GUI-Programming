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
    }
};

#endif // PICTURESORT_H
