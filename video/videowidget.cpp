#include "videowidget.h"

VideoWidget::VideoWidget(QWidget *parent) : QWidget(parent)
{

    QFont font;
    video        = new V4L2_video_class();
    video_thread = new QThread;
    VideoRegim   = new QLabel("ТВШ",this);
    GS           = new QLabel("ГС-",this);
    angle_grid_left = new QLabel("40 т.д.",this);
    angle_grid_right = new QLabel("40 т.д.",this);

     font.setPixelSize(18);

    angle_grid_left->setGeometry(200,550,100,30);
    angle_grid_right->setGeometry(1650,550,100,30);

    angle_grid_left->setFont(font);
    angle_grid_right->setFont(font);

    angle_grid_left->setStyleSheet("QLabel {color : white; }");
    angle_grid_right->setStyleSheet("QLabel {color : white; }");

    VideoRegim->setGeometry(500,30,100,30);
    GS->setGeometry(200,30,100,30);


    GS->setFont(font);
    GS->setAlignment(Qt::AlignCenter);
    GS->setStyleSheet("QLabel { background-color : black; color : white; }");

    VideoRegim->setFont(font);
    VideoRegim->setAlignment(Qt::AlignCenter);
    VideoRegim->setStyleSheet("QLabel { background-color : black; color : white; }");

    video->SetResize(1600,1050);
    video->EnableResize(true);
    // video->CurrentFormatInput();
    haveImage = false;

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
    update();
    haveImage = true;
}

void VideoWidget::paintEvent(QPaintEvent *){

    QPainter painter;
    QPen pen;
    pen.setWidthF(1.0);
    pen.setColor(Qt::white);
    painter.begin(this);
    painter.beginNativePainting();
    painter.setPen(Qt::white);
    int Theight = 1050;
    int Twidth  = 1600;


    if(haveImage) painter.drawImage(40,0,*img);
    painter.setPen(pen);


    painter.translate(Twidth/2.0,Theight/2.0);
    painter.drawLine(-15,0,-Twidth*0.4,0);
    painter.drawLine(15,0,  Twidth*0.4,0);
    painter.drawLine(0,-15,0,-Theight*0.4);
    painter.drawLine(0, 15, 0,Theight*0.4);
    painter.drawRect(-90,-90,180,180);

    for(int i=100;i<Twidth*0.4;i+=100){
        painter.drawLine(20+i,-5,20+i,5);
         painter.drawLine(-20-i,-5,-20-i,5);
    }
    for(int i=100;i<Theight*0.4;i+=100){
        painter.drawLine(5,20+i,-5,20+i);
         painter.drawLine(-5,-20-i,5,-20-i);
    }

    painter.endNativePainting();
    painter.end();
}
VideoWidget::~VideoWidget(){
    delete GS;
    delete VideoRegim;
}
