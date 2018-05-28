#ifndef HUEGENERATOR_H
#define HUEGENERATOR_H

#include <QList>
#include <QColor>
#include <qmath.h>

typedef QList<QColor> ColorVec;


inline ColorVec generate_hues(const QColor color)
{
    ColorVec result;
    result.reserve(12);
    int hue_step = 30;
    int hue = color.hue();
    for (int i=0; i<12; i++)
    {
        int new_hue = qFloor((hue + (i*hue_step)) % 360);
        result.append(QColor::fromHsl(new_hue, color.saturation(), color.lightness()));
    }
    return result;
}

#endif // HUEGENERATOR_H
