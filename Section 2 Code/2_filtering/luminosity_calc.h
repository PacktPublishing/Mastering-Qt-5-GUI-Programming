#ifndef LUMINOSITY_CALC_H
#define LUMINOSITY_CALC_H

#include <QColor>
#include <QImage>
#include <QtMath>
#include <QIcon>


inline qreal get_luminosity(const QColor color)
{
    // Reference: http://www.easyrgb.com/en/math.php
    // RGB to XYZ
    std::array<qreal, 3> rgb{color.redF(), color.greenF(), color.blueF()};
    for (auto it = rgb.begin(); it != rgb.end(); it++)
    {
        if (*it > 0.04045)
            *it = qPow(((*it + 0.055) / 1.055), 2.4) * 100;
        else
            *it = *it / 12.92 * 100;
    }
    // We'll declare the coordinates
    qreal x, y, z;
    x = rgb[0] * 0.4124 + rgb[1] * 0.3576 + rgb[2] * 0.1805;
    y = rgb[0] * 0.2126 + rgb[1] * 0.7152 + rgb[2] * 0.0722;
    z = rgb[0] * 0.0193 + rgb[1] * 0.1192 + rgb[2] * 0.9505;

    x = x/100.;
    y = y/100.;
    z = z/100.;

    std::array<qreal, 3> xyz{x, y, z};

    qreal one_third = 1./3.;

    for (auto it = xyz.begin(); it != xyz.end(); it++)
    {
        if (*it > 0.008856)
        {
            *it = qPow(*it, one_third);
        }
        else
        {
            qreal value = *it;
            *it = (7.787 * value) + (16 / 116);
        }
    }

    // qreal a = 500 * (xyz[0] - xyz[1]);
    // qreal b = 200 * (xyz[1] - xyz[2]);
    qreal luminosity = (116 * xyz[1]) - 16;
    return luminosity;
}

inline qreal icon_to_lumonsity(const QIcon icon)
{
    QImage image = icon.pixmap(50, 50).toImage();
    QColor pixel = image.pixelColor(QPoint(0, 0));
    return get_luminosity(pixel);
}

#endif // LUMINOSITY_CALC_H
