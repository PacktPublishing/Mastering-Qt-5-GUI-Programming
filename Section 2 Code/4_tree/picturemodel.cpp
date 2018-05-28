#include "picturemodel.h"
#include <iostream>


ColorTreeItem* PictureModel::get_item_from_index(const QModelIndex &index) const
{
}


QModelIndex PictureModel::parent(const QModelIndex &index) const
{
}


QModelIndex PictureModel::index(int row, int column, const QModelIndex &parent) const
{
}


QVariant PictureModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // SizeHintRole can be used to change the icon size
    if (role == Qt::SizeHintRole)
        return QSize(50, 50);

    // FIXME: Implement!
    ColorTreeItem* item = ;

    if (role == Qt::DecorationRole)
    {
        // FIXME: Implement!
        return ;
    }
    else if (role == Qt::ToolTipRole)
    {
        // TooolTipRole will be used to display color information on hover
        QVariant data = item->data(index.column());
        QColor c = data.value<QColor>();
        return QString("Hue: " + QString::number(c.hue()) + " Sat: " + QString::number(c.saturation()) + " Val: " + QString::number(c.value()));
    }

    // Fallback for other ItemRoles is to return nothing
    return QVariant();
}

void PictureModel::add_colors(ColorVec colors)
{
    beginInsertRows(QModelIndex(), root_item->childCount(), root_item->childCount() + 1);
    root_item->add_colors(colors);
    endInsertRows();
}

Qt::ItemFlags PictureModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEnabled;
}

int PictureModel::rowCount(const QModelIndex &parent) const
{
    ColorTreeItem* parent_item = get_item_from_index(parent);
    return parent_item->childCount();
}

int PictureModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 12;
}

PictureModel::PictureModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    // root is empty
    root_item = new ColorTreeItem(QList<QVariant>());
}

PictureModel::~PictureModel()
{
    delete root_item;
}
