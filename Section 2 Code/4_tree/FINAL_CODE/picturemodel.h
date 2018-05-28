#ifndef PICTUREMODEL_H 
#define PICTUREMODEL_H 

#include <QAbstractItemModel>
#include "huegenerator.h"
#include "treeitem.h"

class PictureModel: public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit PictureModel(QObject *parent = nullptr);
    ~PictureModel();

    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent=QModelIndex()) const override;
    int columnCount(const QModelIndex &parent=QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void add_colors(ColorVec colors);

private:
    ColorTreeItem* get_item_from_index(const QModelIndex &index) const;

    ColorTreeItem *root_item;
};

#endif // PICTUREMODEL_H 
