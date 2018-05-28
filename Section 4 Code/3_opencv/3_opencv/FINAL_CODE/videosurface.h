#ifndef VIDEOSURFACE_H
#define VIDEOSURFACE_H

#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>
#include <QImage>
#include <QWidget>
#include <QPen>

#include <opencv2/opencv.hpp>


inline cv::Mat qimage_to_mat(QImage &img, int format)
{
    return cv::Mat(img.height(), img.width(), format, const_cast<uchar*>(img.bits()), static_cast<size_t>(img.bytesPerLine()));
}


class VideoSurface : public QAbstractVideoSurface
{
    Q_OBJECT
public:
    VideoSurface(QWidget *video_widget, QObject *parent=nullptr);

    bool start(const QVideoSurfaceFormat &format) override;
    bool present(const QVideoFrame &frame) override;
    void stop() override;

    void resize();
    void paint(QPainter &painter);

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(
            QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const override;

    QVideoSurfaceFormat nearestFormat(const QVideoSurfaceFormat &format) const override;


private:
    cv::Mat _get_mat(QImage image);

    cv::CascadeClassifier _face_classifier;

    QImage::Format _image_format;
    QRect _target_rectangle;
    QSize _image_size;
    QRect _source_rectangle;
    QVideoFrame _current_video_frame;
    QWidget *_video_widget;
    QPen _red_pen;

};

#endif // VIDEOSURFACE_H
