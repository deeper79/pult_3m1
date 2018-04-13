#include "videowidget.h"

VideoWidget::VideoWidget(QWidget *parent) : QWidget(parent)
{
    video        = new V4L2_video_class();
    video_thread = new QThread;

    connect(video,SIGNAL(haveFrame(QImage *)),this,SLOT(reciveImage(QImage *)));
    connect(video_thread,SIGNAL(started()),video,SLOT(MainLoop()));
    video->moveToThread(video_thread);
}
void VideoWidget::start() const{
    const char* dev = "/dev/video1";
    video->SetResize(1920,1200);
    video->OpenDevice(dev);
    video->InitDevice();
    video->StartCapturing();
    video_thread->start();
}
void VideoWidget::stop()  const{
    video->StopCapturing();
    video->DeInitDevice();
    video_thread->quit();
}

void VideoWidget::reciveImage(QImage *in){
    img = in;
}
