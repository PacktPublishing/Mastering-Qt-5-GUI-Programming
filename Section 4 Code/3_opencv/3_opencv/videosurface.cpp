#include "videosurface.h"
#include <QPainter>
#include <QDir>
#include <QCoreApplication>
#include <QResource>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <QDebug>
#include <QGraphicsItem>


VideoSurface::VideoSurface(QWidget *video_widget, QObject *parent)
       : QAbstractVideoSurface(parent)
	, _video_widget(video_widget)
{
    QDir executable_directory(QCoreApplication::applicationDirPath());
    QString filename("haarcascade_frontalface_default.xml");
    _red_pen.setColor(Qt::red);
    _red_pen.setWidth(10);
}

void VideoSurface::paint(QPainter &painter)
{
    if (_current_video_frame.map(QAbstractVideoBuffer::ReadOnly)) {
        QImage image(
                _current_video_frame.bits(),
                _current_video_frame.width(),
                _current_video_frame.height(),
                _current_video_frame.bytesPerLine(),
                _image_format);

        cv::Mat gray_mat_image = _get_mat(image);
        cv::Size max_face_size(gray_mat_image.cols/4, gray_mat_image.rows/4);

        std::vector<cv::Rect> faces;

        for (cv::Rect rectangle: faces)
        {
            QPoint top_left(rectangle.tl().x, rectangle.tl().y);
            QPoint bottom_right(rectangle.br().x, rectangle.br().y);
        }

        if (surfaceFormat().scanLineDirection() == QVideoSurfaceFormat::BottomToTop) {
           const QTransform old_transform = painter.transform();
           painter.scale(1, -1);
           painter.translate(0, -_video_widget->height());
           painter.drawImage(_target_rectangle, image, _source_rectangle);
           painter.setTransform(old_transform);
        } else {
            painter.drawImage(_target_rectangle, image, _source_rectangle);
        }

        qDebug() << "Size: " << faces.size();

        _current_video_frame.unmap();
    }
}

cv::Mat VideoSurface::_get_mat(QImage image)
{
    cv::Mat mat_image;
    switch (image.format())
    {
    case QImage::Format_RGB32:
    {
        mat_image = qimage_to_mat(image, CV_8UC4);
        cv::Mat gray_mat_image;
        cv::cvtColor(mat_image, gray_mat_image, cv::COLOR_BGRA2BGR);
        cv::cvtColor(gray_mat_image, gray_mat_image, CV_BGR2GRAY);
        cv::equalizeHist(gray_mat_image, gray_mat_image);
        return gray_mat_image;
    }
    case QImage::Format_RGB888:{
        mat_image = qimage_to_mat(image, CV_8UC3);
        cv::cvtColor(mat_image, mat_image, CV_RGB2BGR);
        break;
    }
    case QImage::Format_Indexed8:
    {
        mat_image = qimage_to_mat(image, CV_8U);
        break;
    }
    case QImage::Format_ARGB32:
    case QImage::Format_ARGB32_Premultiplied:
    {
        mat_image = qimage_to_mat(image, CV_8UC4);
        break;
    }
    default:
        qWarning() << "QImage format not handled in switch: " << image.format();
        break;
    }
    // NOTE: If we made it here, sucessfully created `cv::Mat mat_image`
}

void VideoSurface::resize()
{
    QSize size = surfaceFormat().sizeHint();
    // scale the size of things
    size.scale(_video_widget->size().boundedTo(size), Qt::KeepAspectRatio);

    _target_rectangle = QRect(QPoint(0, 0), size);
    // align the rectangle in the center
    _target_rectangle.moveCenter(_video_widget->rect().center());
}


QVideoSurfaceFormat VideoSurface::nearestFormat(const QVideoSurfaceFormat &format) const
{
}

QList<QVideoFrame::PixelFormat> VideoSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const
{
    if (handleType == QAbstractVideoBuffer::NoHandle)
    {
        return QList<QVideoFrame::PixelFormat>()
                << QVideoFrame::Format_RGB32
                << QVideoFrame::Format_ARGB32
                << QVideoFrame::Format_ARGB32_Premultiplied
                << QVideoFrame::Format_RGB24;
    } else
        return QList<QVideoFrame::PixelFormat>();
}

bool VideoSurface::present(const QVideoFrame &frame)
{
    if (surfaceFormat().pixelFormat() != frame.pixelFormat()
            || surfaceFormat().frameSize() != frame.size())
    {
        setError(IncorrectFormatError);
        stop();

        return false;
    }
    else {
        _current_video_frame = frame;

        _video_widget->repaint(_target_rectangle);

        return true;
    }
}

void VideoSurface::stop()
{
    _current_video_frame = QVideoFrame();
    _target_rectangle = QRect();
    QAbstractVideoSurface::stop();
    _video_widget->update();
}

bool VideoSurface::start(const QVideoSurfaceFormat &format)
{
     const QImage::Format image_format = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());
     const QSize size = format.frameSize();

     if (image_format != QImage::Format_Invalid && !size.isEmpty()) {
         _image_format = image_format;
         _image_size = size;
         _source_rectangle = format.viewport();

         QAbstractVideoSurface::start(format);

         _video_widget->updateGeometry();
         resize();

         return true;
     } else {
         return false;
     }
}

