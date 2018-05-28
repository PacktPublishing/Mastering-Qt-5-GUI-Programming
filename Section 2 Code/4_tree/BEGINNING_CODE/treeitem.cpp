#include "treeitem.h"

ColorTreeItem::ColorTreeItem(const QList<QVariant> &data, ColorTreeItem *parent):
    _color_data(data),
    _parent_item(parent)
{
}

ColorTreeItem::~ColorTreeItem()
{
    qDeleteAll(_child_items);
}

ColorTreeItem *ColorTreeItem::child(int number)
{
    return _child_items.value(number);
}

int ColorTreeItem::childCount() const
{
    return _child_items.count();
}

int ColorTreeItem::childNumber() const
{
    if (_parent_item)
        return _parent_item->_child_items.indexOf(const_cast<ColorTreeItem*>(this));

    return 0;
}

int ColorTreeItem::columnCount() const
{
    return _color_data.count();
}

QVariant ColorTreeItem::data(int column) const
{
    return _color_data.value(column);
}


ColorTreeItem *ColorTreeItem::parent()
{
    return _parent_item;
}

void ColorTreeItem::appendChild(ColorTreeItem *child)
{
    _child_items.append(child);
}

void ColorTreeItem::add_colors(QList<QColor> colors)
{
    QVariant color_data = colors[0];
    QList<QVariant> original_data;
    original_data << color_data;
    ColorTreeItem* original_color = new ColorTreeItem(original_data, this);
    appendChild(original_color);

    QList<QVariant> recommended_colorscheme_data;
    recommended_colorscheme_data << QVariant();
    for (int i = 1; i < colors.size(); i++)
    {
        QVariant v = colors[i];
        recommended_colorscheme_data << v;
    }

    ColorTreeItem* recommended_colorscheme = new ColorTreeItem(recommended_colorscheme_data, original_color);
    original_color->appendChild(recommended_colorscheme);

}
