#include "videowidget.h"


VideoWidget::VideoWidget(QWidget *parent) : QWidget(parent)
{
    _video_surface = new VideoSurface(this);
}


void VideoWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    _video_surface->paint(painter);
    painter.end();
}

void VideoWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    _video_surface->resize();
}
