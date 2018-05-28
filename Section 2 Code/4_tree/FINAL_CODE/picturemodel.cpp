#include "picturemodel.h"
#include <iostream>


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

QModelIndex PictureModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    ColorTreeItem* parent_item = get_item_from_index(parent);
    ColorTreeItem *child_item = parent_item->child(row);

    if (child_item)
        return createIndex(row, column, child_item);
    else
        return QModelIndex();
}

QModelIndex PictureModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    ColorTreeItem *child_item = get_item_from_index(index);
    ColorTreeItem *parent_item = child->parent();

    if (parent_item == root_item)
        return QModelIndex();

    // By common convention, only items in the first column have children.
    return createIndex(parent->childNumber(), 0, parent);
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

QVariant PictureModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // SizeHintRole can be used to change the icon size
    if (role == Qt::SizeHintRole)
        return QSize(50, 50);

    // Get our item!
    ColorTreeItem* item = get_item_from_index(index);

    if (role == Qt::DecorationRole)
    {
        // TODO: Implement
        return item->data(index.column());
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

ColorTreeItem* PictureModel::get_item_from_index(const QModelIndex &index) const
{
    if (index.isValid())
    {
        ColorTreeItem* item = static_cast<ColorTreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return root_item;
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
