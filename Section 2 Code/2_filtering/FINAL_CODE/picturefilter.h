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

    void set_min_filter_value(qreal lumonsity)
    {
        min_filter_value = lumonsity;
        invalidateFilter();
    }

    void set_max_filter_value(qreal lumonsity)
    {
        max_filter_value = lumonsity;
        invalidateFilter();
    }

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
    {
        int column = 0;
        QModelIndex picture_index = sourceModel()->index(source_row, column, source_parent);
        QVariant data = picture_index.data(Qt::DecorationRole);
        QIcon icon = data.value<QIcon>();
        qreal lum =icon_to_lumonsity(icon);
        return lum > min_filter_value && lum < max_filter_value;
    }

private:
    qreal min_filter_value;
    qreal max_filter_value;
};

#endif // PICTURESORT_H
