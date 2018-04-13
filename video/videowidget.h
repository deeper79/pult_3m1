#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QWidget>
#include "video.h"
#include <QThread>
#include <QLabel>
#include <QPushButton>

class VideoWidget : public QWidget
{
    Q_OBJECT
public:
    ~VideoWidget(void);
    explicit VideoWidget(QWidget *parent = 0);
    void start(void) const;
    void stop(void)  const;

private:
    V4L2_video_class  *video;
    QThread           *video_thread;
    QImage            *img;
    QLabel            *VideoRegim;
    QLabel            *GS;
    QLabel            *angle_grid_left;
    QLabel            *angle_grid_right;
    bool haveImage;
   // QAbstracVideoFusface;

protected:
    void paintEvent(QPaintEvent *);

public slots:
    void reciveImage(QImage *in);
};

#endif // VIDEOWIDGET_H
