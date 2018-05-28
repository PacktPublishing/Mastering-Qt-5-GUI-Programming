#include "photomodel.h"

#include <QString>
#include <QColor>
#include <iostream>
#include <random>

PhotoModel::PhotoModel(QObject *parent)
    : QAbstractListModel(parent)
{
    setup_virdis_values();
    int num_colors = 100;
    std::random_device rd;
    std::mt19937 end(rd());
    std::uniform_int_distribution<> distr(0, 255);

    colors.reserve(num_colors);
    for (int i = 0; i < num_colors; i++)
    {
        QColor color = _viridis_values[distr(end)];
        colors.append(color);
    }
}

int PhotoModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return colors.size();
}


QVariant PhotoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DecorationRole)
        return colors[index.row()];

    return QVariant();
}

bool PhotoModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(data(index, role) != value)
    {
        colors[index.row()] = value.value<QColor>();
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }

    return false;
}

Qt::ItemFlags PhotoModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEnabled;

}

void PhotoModel::setup_virdis_values()
{
    _viridis_values = QVector<QColor>{
            QColor(68, 1, 84),
            QColor(68, 2, 85),
            QColor(69, 3, 87),
            QColor(69, 5, 88),
            QColor(69, 6, 90),
            QColor(70, 8, 91),
            QColor(70, 9, 93),
            QColor(70, 11, 94),
            QColor(70, 12, 96),
            QColor(71, 14, 97),
            QColor(71, 15, 98),
            QColor(71, 17, 100),
            QColor(71, 18, 101),
            QColor(71, 20, 102),
            QColor(72, 21, 104),
            QColor(72, 22, 105),
            QColor(72, 24, 106),
            QColor(72, 25, 108),
            QColor(72, 26, 109),
            QColor(72, 28, 110),
            QColor(72, 29, 111),
            QColor(72, 30, 112),
            QColor(72, 32, 113),
            QColor(72, 33, 115),
            QColor(72, 34, 116),
            QColor(72, 36, 117),
            QColor(72, 37, 118),
            QColor(72, 38, 119),
            QColor(72, 39, 120),
            QColor(71, 41, 121),
            QColor(71, 42, 121),
            QColor(71, 43, 122),
            QColor(71, 44, 123),
            QColor(71, 46, 124),
            QColor(70, 47, 125),
            QColor(70, 48, 126),
            QColor(70, 49, 126),
            QColor(70, 51, 127),
            QColor(69, 52, 128),
            QColor(69, 53, 129),
            QColor(69, 54, 129),
            QColor(68, 56, 130),
            QColor(68, 57, 131),
            QColor(68, 58, 131),
            QColor(67, 59, 132),
            QColor(67, 60, 132),
            QColor(67, 62, 133),
            QColor(66, 63, 133),
            QColor(66, 64, 134),
            QColor(65, 65, 134),
            QColor(65, 66, 135),
            QColor(65, 67, 135),
            QColor(64, 69, 136),
            QColor(64, 70, 136),
            QColor(63, 71, 136),
            QColor(63, 72, 137),
            QColor(62, 73, 137),
            QColor(62, 74, 137),
            QColor(61, 75, 138),
            QColor(61, 77, 138),
            QColor(60, 78, 138),
            QColor(60, 79, 138),
            QColor(59, 80, 139),
            QColor(59, 81, 139),
            QColor(58, 82, 139),
            QColor(58, 83, 139),
            QColor(57, 84, 140),
            QColor(57, 85, 140),
            QColor(56, 86, 140),
            QColor(56, 87, 140),
            QColor(55, 88, 140),
            QColor(55, 89, 140),
            QColor(54, 91, 141),
            QColor(54, 92, 141),
            QColor(53, 93, 141),
            QColor(53, 94, 141),
            QColor(52, 95, 141),
            QColor(52, 96, 141),
            QColor(51, 97, 141),
            QColor(51, 98, 141),
            QColor(51, 99, 141),
            QColor(50, 100, 142),
            QColor(50, 101, 142),
            QColor(49, 102, 142),
            QColor(49, 103, 142),
            QColor(48, 104, 142),
            QColor(48, 105, 142),
            QColor(47, 106, 142),
            QColor(47, 107, 142),
            QColor(47, 108, 142),
            QColor(46, 109, 142),
            QColor(46, 110, 142),
            QColor(45, 111, 142),
            QColor(45, 112, 142),
            QColor(45, 112, 142),
            QColor(44, 113, 142),
            QColor(44, 114, 142),
            QColor(43, 115, 142),
            QColor(43, 116, 142),
            QColor(43, 117, 142),
            QColor(42, 118, 142),
            QColor(42, 119, 142),
            QColor(41, 120, 142),
            QColor(41, 121, 142),
            QColor(41, 122, 142),
            QColor(40, 123, 142),
            QColor(40, 124, 142),
            QColor(40, 125, 142),
            QColor(39, 126, 142),
            QColor(39, 127, 142),
            QColor(38, 128, 142),
            QColor(38, 129, 142),
            QColor(38, 130, 142),
            QColor(37, 131, 142),
            QColor(37, 131, 142),
            QColor(37, 132, 142),
            QColor(36, 133, 142),
            QColor(36, 134, 142),
            QColor(35, 135, 142),
            QColor(35, 136, 142),
            QColor(35, 137, 142),
            QColor(34, 138, 141),
            QColor(34, 139, 141),
            QColor(34, 140, 141),
            QColor(33, 141, 141),
            QColor(33, 142, 141),
            QColor(33, 143, 141),
            QColor(32, 144, 141),
            QColor(32, 145, 140),
            QColor(32, 146, 140),
            QColor(32, 147, 140),
            QColor(31, 147, 140),
            QColor(31, 148, 140),
            QColor(31, 149, 139),
            QColor(31, 150, 139),
            QColor(31, 151, 139),
            QColor(30, 152, 139),
            QColor(30, 153, 138),
            QColor(30, 154, 138),
            QColor(30, 155, 138),
            QColor(30, 156, 137),
            QColor(30, 157, 137),
            QColor(30, 158, 137),
            QColor(30, 159, 136),
            QColor(30, 160, 136),
            QColor(31, 161, 136),
            QColor(31, 162, 135),
            QColor(31, 163, 135),
            QColor(31, 163, 134),
            QColor(32, 164, 134),
            QColor(32, 165, 134),
            QColor(33, 166, 133),
            QColor(33, 167, 133),
            QColor(34, 168, 132),
            QColor(35, 169, 131),
            QColor(35, 170, 131),
            QColor(36, 171, 130),
            QColor(37, 172, 130),
            QColor(38, 173, 129),
            QColor(39, 174, 129),
            QColor(40, 175, 128),
            QColor(41, 175, 127),
            QColor(42, 176, 127),
            QColor(43, 177, 126),
            QColor(44, 178, 125),
            QColor(46, 179, 124),
            QColor(47, 180, 124),
            QColor(48, 181, 123),
            QColor(50, 182, 122),
            QColor(51, 183, 121),
            QColor(53, 183, 121),
            QColor(54, 184, 120),
            QColor(56, 185, 119),
            QColor(57, 186, 118),
            QColor(59, 187, 117),
            QColor(61, 188, 116),
            QColor(62, 189, 115),
            QColor(64, 190, 114),
            QColor(66, 190, 113),
            QColor(68, 191, 112),
            QColor(70, 192, 111),
            QColor(72, 193, 110),
            QColor(73, 194, 109),
            QColor(75, 194, 108),
            QColor(77, 195, 107),
            QColor(79, 196, 106),
            QColor(81, 197, 105),
            QColor(83, 198, 104),
            QColor(85, 198, 102),
            QColor(88, 199, 101),
            QColor(90, 200, 100),
            QColor(92, 201, 99),
            QColor(94, 201, 98),
            QColor(96, 202, 96),
            QColor(98, 203, 95),
            QColor(101, 204, 94),
            QColor(103, 204, 92),
            QColor(105, 205, 91),
            QColor(108, 206, 90),
            QColor(110, 206, 88),
            QColor(112, 207, 87),
            QColor(115, 208, 85),
            QColor(117, 208, 84),
            QColor(119, 209, 82),
            QColor(122, 210, 81),
            QColor(124, 210, 79),
            QColor(127, 211, 78),
            QColor(129, 212, 76),
            QColor(132, 212, 75),
            QColor(134, 213, 73),
            QColor(137, 213, 72),
            QColor(139, 214, 70),
            QColor(142, 215, 68),
            QColor(144, 215, 67),
            QColor(147, 216, 65),
            QColor(149, 216, 63),
            QColor(152, 217, 62),
            QColor(155, 217, 60),
            QColor(157, 218, 58),
            QColor(160, 218, 57),
            QColor(163, 219, 55),
            QColor(165, 219, 53),
            QColor(168, 220, 51),
            QColor(171, 220, 50),
            QColor(173, 221, 48),
            QColor(176, 221, 46),
            QColor(179, 221, 45),
            QColor(181, 222, 43),
            QColor(184, 222, 41),
            QColor(187, 223, 39),
            QColor(189, 223, 38),
            QColor(192, 223, 36),
            QColor(195, 224, 35),
            QColor(197, 224, 33),
            QColor(200, 225, 32),
            QColor(203, 225, 30),
            QColor(205, 225, 29),
            QColor(208, 226, 28),
            QColor(211, 226, 27),
            QColor(213, 226, 26),
            QColor(216, 227, 25),
            QColor(219, 227, 24),
            QColor(221, 227, 24),
            QColor(224, 228, 24),
            QColor(226, 228, 24),
            QColor(229, 228, 24),
            QColor(232, 229, 25),
            QColor(234, 229, 25),
            QColor(237, 229, 26),
            QColor(239, 230, 27),
            QColor(242, 230, 28),
            QColor(244, 230, 30),
            QColor(247, 230, 31),
            QColor(249, 231, 33),
            QColor(251, 231, 35),
            QColor(254, 231, 36)};
}
