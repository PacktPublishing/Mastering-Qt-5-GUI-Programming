#ifndef PICTURESORT_H
#define PICTURESORT_H

#include <QSortFilterProxyModel>
#include "luminosity_calc.h"


class PictureFilter: public QSortFilterProxyModel
{
public:
    PictureFilter(QObject *parent=0):
        QSortFilterProxyModel(parent),
        min_filter_value(0.),
        max_filter_value(100.)
    {
    }

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
    {

    }

private:
    qreal min_filter_value;
    qreal max_filter_value;
};

#endif // PICTURESORT_H
