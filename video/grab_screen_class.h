#ifndef GRAB_SCREEN_CLASS_H
#define GRAB_SCREEN_CLASS_H

#include <QObject>
#include <QScreen>
#include <QImage>
#include <QPixmap>
#include <QTimer>
#include <QDebug>
#include <QDateTime>
#include <QDir>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <X11/extensions/XShm.h>

#include <ippi.h>
#include <ippcore.h>
#include <ippcore_l.h>
#include <ippvm.h>
#include <ipps.h>
#include <ippcc.h>


extern "C" {
#include <libavutil/opt.h>
#include <libavcodec/avcodec.h>
#include <libavutil/channel_layout.h>
#include <libavutil/common.h>
#include <libavutil/imgutils.h>
#include <libavutil/mathematics.h>
#include <libavutil/samplefmt.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

//#include "libavcodec/avcodec.h"

//#include "libavutil/"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <QMutex>




class grab_screen_class : public QObject
{
    Q_OBJECT
public:
    explicit grab_screen_class(QObject *parent = nullptr);
    ~grab_screen_class();
    //void SetScreen(QList<QScreen*> scn){screen = scn;}

    void TimerStart(int milsec){

        timer->start(milsec);
    }
    bool StartRecord(void);
    void StopRecord(void);


private:
    bool init(void);

   // QList<QScreen*> screen;

    QTimer  *timer;
    AVCodec *codec;
    AVCodecContext *context= NULL;
    FILE *fp;
    AVFrame  *frame_in_fist;
    AVFrame  *frame_in_second;
    AVFrame  *frame_in_out;
    AVPacket *pkt;
    XImage* ximg;
    Screen* screen;

    Display *display ;
    Window root;
    XShmSegmentInfo shminfo;
    QString filename;
    bool screenGrab;
    QMutex	m_mutex;
    SwsContext *ctx;

signals:
    void finished(void);
    void StartEncode (void);


public slots:
     void GrabScreen();
     void EndEncode(void);


};

#endif // GRAB_SCREEN_CLASS_H
