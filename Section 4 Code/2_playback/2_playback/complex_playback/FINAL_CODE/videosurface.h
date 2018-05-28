#ifndef VIDEOSURFACE_H
#define VIDEOSURFACE_H

#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>
#include <QImage>
#include <QWidget>


class VideoSurface : public QAbstractVideoSurface
{
    Q_OBJECT
public:
    VideoSurface(QWidget *video_widget, QObject *parent=nullptr);

    bool start(const QVideoSurfaceFormat &format) override;
    void stop() override;

    bool present(const QVideoFrame &frame) override;

    // Helper methods called by the container widget
    void resize();
    void paint(QPainter &painter);

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(
            QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const override;
    QVideoSurfaceFormat nearestFormat(const QVideoSurfaceFormat &format) const override;


private:
    QVideoFrame _current_video_frame;
    QImage::Format _image_format;
    QSize _image_size;
    QWidget *_video_widget;

    // NOTE: Used for scaling with the `QPainter::drawImage` function
    QRect _target_rectangle;
    QRect _source_rectangle;

};

#endif // VIDEOSURFACE_H
