#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QColor>
#include <QVector>
#include <QVariant>

class ColorTreeItem
{
public:
    explicit ColorTreeItem(const QList<QVariant> &data, ColorTreeItem *parent = 0);
    ~ColorTreeItem();

    ColorTreeItem *parent();
    ColorTreeItem *child(int number);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int childNumber() const;
    void add_colors(QList<QColor> colors);
    void appendChild(ColorTreeItem* child);

private:
    QList<ColorTreeItem*> _child_items;
    QList<QVariant> _color_data;
    ColorTreeItem *_parent_item;
};


#endif // TREEITEM_H
