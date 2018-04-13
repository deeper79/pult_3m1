#include "grab_screen_class.h"

grab_screen_class::grab_screen_class(QObject *parent) : QObject(parent)
{
    timer = new QTimer();
    av_register_all();
    screenGrab = false;
    timer->setInterval(40);
    init();
    connect(timer,SIGNAL(timeout()),this,SLOT(GrabScreen()));
    connect(this,SIGNAL(StartEncode()),timer,SLOT(start()));
    connect(this,SIGNAL(finished()),this,SLOT(EndEncode()));
    connect(this,SIGNAL(finished()),timer,SLOT(stop()));
}

void grab_screen_class::EndEncode(void){

    
   
    uint8_t endcode[] = { 0, 0, 1, 0xb7 };

    fwrite(endcode, 1, sizeof(endcode), fp);
    fclose(fp);
    
    XShmDetach(display,&shminfo);
    XDestroyImage(ximg);
    shmdt(shminfo.shmaddr);
    XCloseDisplay(display);
    sws_freeContext(ctx);

   avcodec_close(context);
   av_free(context);
   av_frame_free(&frame_in_fist);
   //av_freep(&frame_in_fist->data[0]);


   av_frame_free(&frame_in_out);
   //av_freep(&frame_in_out->data[0]);

}
bool grab_screen_class::StartRecord(){

    QDir dir;
    QDateTime time = QDateTime::currentDateTime();
    filename = QString("/mnt/video/record/" + QString(time.toString("hh:mm:ss_dd_MM_yyyy")) + "/"+
                       "record_pribor_3m1_RLS_" +
                       time.toString("hh:mm:ss_dd_MM_yyyy")+".avi");
    dir.mkdir("/mnt/video/record/" +QString(time.toString("hh:mm:ss_dd_MM_yyyy")));

    fp = fopen(filename.toUtf8().constData(),"wb");

    if(!fp){
        qDebug()<<"Could not open file" << filename;
        return false;
    }
    init();
    emit StartEncode();

    //timer->start(40);


    return true;
}

void grab_screen_class::StopRecord(){

    emit finished();

    return;
}
bool grab_screen_class::init(){
    XWindowAttributes window_attributes;

    display = XOpenDisplay(NULL);
    root = DefaultRootWindow(display);
    XGetWindowAttributes(display,root,&window_attributes);
    screen = window_attributes.screen;

    ximg = XShmCreateImage(display,
                           DefaultVisualOfScreen(screen),
                           DefaultDepthOfScreen(screen),
                           ZPixmap,
                           NULL,
                           &shminfo,
                           1600,
                           screen->height);

    shminfo.shmid = shmget(IPC_PRIVATE, ximg->bytes_per_line * ximg->height, IPC_CREAT|0777);
    shminfo.shmaddr = ximg->data = (char*)shmat(shminfo.shmid, 0, 0);
    shminfo.readOnly = False;

    XShmAttach(display, &shminfo);

    pkt = av_packet_alloc();

    frame_in_fist   = av_frame_alloc();
    frame_in_out    = av_frame_alloc();


    codec = avcodec_find_encoder(AV_CODEC_ID_H264);
    if(!codec){
        qDebug()<<"codec not found" <<  strerror(errno);
        return false;
    }

    context = avcodec_alloc_context3(codec);

    if(!context){
        qDebug()<<"Could not allocate video codec context" << strerror(errno);
        return false;
    }

    context->bit_rate = 2800000;
    context->width    = 1600;
    context->height   = 1200;

    context->time_base.num =  1;
    context->time_base.den = 25;

    context->framerate.num = 25;
    context->framerate.den =  1;
    context->gop_size = 10;
    context->max_b_frames = 1;

    context->pix_fmt = AV_PIX_FMT_YUV420P;

    if(avcodec_open2(context,codec,NULL)<0){
        qDebug()<<"Could not open codec" <<  strerror(errno);
        return false;
    }

    av_opt_set(context->priv_data, "preset", "slow", 0);

    frame_in_fist->format = AV_PIX_FMT_RGB32;
    frame_in_fist->width  = ximg->width;
    frame_in_fist->height = ximg->height;

    frame_in_out->format = AV_PIX_FMT_YUV420P;
    frame_in_out->width  =  ximg->width;
    frame_in_out->height =  ximg->height;


    av_image_alloc(frame_in_fist->data,frame_in_fist->linesize,frame_in_fist->width,frame_in_fist->height,AV_PIX_FMT_RGB32,1);
    av_image_alloc(frame_in_out->data,frame_in_out->linesize,frame_in_out->width,frame_in_out->height,AV_PIX_FMT_YUV420P,1);

    int    ret = av_frame_get_buffer(frame_in_fist,32);

    if(ret<0){
        qDebug()<<"Could not allocate raw picture buffer 1 ";
        return false;
    }

    ret = av_frame_get_buffer(frame_in_out,32);

    if(ret<0){
        qDebug()<<"Could not allocate raw picture buffer 2";
        return false;
    }

    ctx=sws_getContext(
                ximg->width, ximg->height,AV_PIX_FMT_RGB32,
                ximg->width, ximg->height,AV_PIX_FMT_YUV420P,
                0,0,0,0);

    return true;
}


void grab_screen_class::GrabScreen(){

    static int count = 0;
    screenGrab= true;

    Ipp8u *pDst[3];
    IppiSize size;
    IppStatus status;

    QTime time;

    //   pDst = ippsMalloc_8u(ximg->width*ximg->height*3);

    XShmGetImage(display, root, ximg, 0, 0, 0x00ffffff);
    size.height = ximg->height;
    size.width  = ximg->width;
    *frame_in_fist->data = (uint8_t *)ximg->data;

    //pDst = (Ipp8u *)malloc(3*sizeof(Ipp8u));
    //*pDst[0] =(Ipp8u)frame_in_fist->linesize[0];


    //status = ippiRGBToYUV420_8u_C3P3((Ipp8u* )ximg->data,pDst,size);
    //  time.start();
    // for(int i=0;i<100;i++)

    // m_mutex.lock();
    int out;

    out = sws_scale(ctx,frame_in_fist->data,
                    frame_in_fist->linesize,
                    0,
                    context->height,
                    frame_in_out->data,
                    frame_in_out->linesize);




    count++;
    frame_in_out->pts = count;

    int ret = avcodec_send_frame(context,frame_in_out);

    if(ret < 0){
        qDebug()<<"error sending a frame for encoding" << strerror(errno);
        return;
    }

    while(ret >=0){
        ret = avcodec_receive_packet(context,pkt);
        if(ret  == AVERROR(EAGAIN) || ret == AVERROR_EOF)
            return;

        else if(ret < 0){
            qDebug()<<"Could not allocate raw picture buffer";
            return;
        }

        fwrite(pkt->data, 1, pkt->size, fp);
        av_packet_unref(pkt);

    }


}

grab_screen_class::~grab_screen_class(){



}
