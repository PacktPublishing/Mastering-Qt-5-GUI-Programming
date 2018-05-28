#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QVector>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <qdrawutil.h>


class ColorPicker : public QWidget
{
    Q_OBJECT
public:
    ColorPicker(QColor color, QWidget* parent=0);
    ~ColorPicker();

    QColor current_color;

signals:
    void new_color(QColor val);

protected:
    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    QSize sizeHint() const;

private:
    enum { foff = 3, coff = 4 }; //frame and contents offset
    void set_color(QColor color);

    QColor y_to_color(int y);
    int color_to_y(QColor color);

    QPixmap *pix;
    QVector<QColor> viridis_values;
};
#endif // COLORPICKER_H
