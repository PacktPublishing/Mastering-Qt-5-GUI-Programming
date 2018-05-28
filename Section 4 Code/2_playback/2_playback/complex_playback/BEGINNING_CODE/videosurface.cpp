#include "videosurface.h"
#include <QPainter>
#include <QDebug>


VideoSurface::VideoSurface(QWidget *video_widget, QObject *parent) :
    QAbstractVideoSurface(parent),
    _video_widget(video_widget)
{
}

bool VideoSurface::start(const QVideoSurfaceFormat &format)
{
     const QSize size = ;
     const QImage::Format image_format = ;

     // TODO: Check to see if the format is valid and the frame is actually a size
     if () {
         return false;
     } else {
     // if we made it here, we're in business!
     // store image format
     _image_format = image_format;
     // store the video size
     _image_size = size;

     _source_rectangle = format.viewport();

     // call our parent class
     QAbstractVideoSurface::start(format);

     // make sure the parent class's geometry is correct
     _video_widget->updateGeometry();
     // and resize
     resize();

         return true;
     }
}

void VideoSurface::resize()
{
    // How big is the video coming in?
    QSize video_size = surfaceFormat().sizeHint();
    // How big is the parent widget?
    QSize widget_size = _video_widget->size();
    // scale the video size to our widget size, keeping the aspect ratio
    video_size.scale(widget_size.boundedTo(video_size), Qt::KeepAspectRatio);

    // Target is the widget we're going to paint too
    _target_rectangle = QRect(QPoint(0, 0), video_size);
    // align the rectangle in the center
    _target_rectangle.moveCenter(_video_widget->rect().center());
}

bool VideoSurface::present(const QVideoFrame &frame)
{
    // check to make sure that our user didn't switch between the
    // `start` method and the `present` method by checking the
    // formats and the frame size.
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

void VideoSurface::paint(QPainter &painter)
{
    if () {
        QImage image();

        if () {}
        else
            ;
    }
}

void VideoSurface::stop()
{
    _current_video_frame = QVideoFrame();
    _target_rectangle = QRect();
    QAbstractVideoSurface::stop();
    _video_widget->update();
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

QVideoSurfaceFormat VideoSurface::nearestFormat(const QVideoSurfaceFormat &format) const
{
    // NOTE: must override per the base class. Per Qt's own concret implementation of this class,
    // this method is not used.
    // see: https://github.com/qt/qtmultimedia/blob/5.11/src/multimediawidgets/qpaintervideosurface_p.h#L71
    // Unsure the utility of this function.
}

