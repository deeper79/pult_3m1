#include "pult_3m1_main_class.h"

pult_3m1_main_class::pult_3m1_main_class(QWidget *parent)
    : QWidget(parent),height(1080),width(1920)
{
    QPalette pal;
    setGeometry(0,0,1600,1200);
    setAutoFillBackground(true);
    pal.setColor(backgroundRole(),Qt::darkGreen);

    Q_INIT_RESOURCE(resurces);

    setPalette(pal);

    side = right;
    vizir_angle  = 0;
    kurs_angle   = 0;
    zahvat_angle = 0;
    UM    =   0;
    Dalnost = 15000;
    Amper =0;

    listScreen = QApplication::screens();

    scan              = new scanning_class(this,0,0);           // создание объекта рисования развертки по КУ
    scan_um           = new UM_scannig_class(this,1087,10);     // создание объекта рисования развертки по УМ
    autotrack_dalnost = new autotrack_dalnost_class(this,1100,780);     // созднаие объекта отрисовки ошибки автосопровождения
    panel_vizir       = new panel_vizir_class(1,1100,this);     // создание панели "Положение визира"
    panel_antena      = new panel_antena_class(255,1100,this);  // создание панели "Положение антены"
    panel_param       = new panel_param_class(510,1100,this);   // создание панели "Параметров движения цели"
    panel_error       = new panel_error_class(1085,1100,this); //
    panel_RLS         = new panel_RLS_class(1100,420,this);
    miliampermeter    = new miliampermeter_class(this,920,945);
    tou_keyboard      = new tou_keyboard_class();
    video             = new VideoWidget();
    regim             = new QLabel(this);                       // созднаие надписи текущего режима
    date              = new QLabel(this);
    MOC               = new QLabel("МОС ВЫКЛ.",this);
    time              = new QDateTime();
    timer             = new QTimer();
    timer_draw        = new QTimer();
    text_sloi         = new QLabel("2",this);
    text_zona         = new QLabel("нижняя",this);
    QLabel *sloi      = new QLabel("СЛОЙ",this);
    QLabel *zona      = new QLabel("ЗОНА",this);
    QLabel *ICOS      = new QLabel("ИКОС",this);
    QLabel *regim_l   = new QLabel("Режим",this);
    anim1             = new QPropertyAnimation(this,"geometry");
    anim2             = new QPropertyAnimation(video,"geometry");
    grabScreen        = new grab_screen_class();
    ThreadGrabScreen  = new QThread();
    usb_mko_pribor1m  = new usb_mko_Pribor1M_class();

    memset((uchar *)Data_in_BC123.data,0x00,sizeof(Data_in_BC123.data));

    Data_in_BC123.SD1.Shire = 1;

    //grabScreen->SetScreen(listScreen);
     grabScreen->moveToThread(ThreadGrabScreen);
     ThreadGrabScreen->start();


    //  scan->SetScreen(listScreen[2]);
   // grabScreen->TimerStart(40);

    anim1->setDuration(300);
    anim2->setDuration(300);

   // tou_keyboard ->setGeometry(3280,0,1024,768);
  //  tou_keyboard ->show();

    video        ->setGeometry(1600,0,1600,1200);
    video        ->show();
    video->start();


    sloi->setStyleSheet("background: blue;font-size: 18px;color: yellow; border: 2px solid white;");
    sloi->setAlignment(Qt::AlignCenter);
    sloi->setGeometry(950,20,100,30);

    zona->setStyleSheet("background: blue;font-size: 18px;color: yellow; border: 2px solid white;");
    zona->setAlignment(Qt::AlignCenter);
    zona->setGeometry(950,120,100,30);

    text_sloi->setStyleSheet("background: blue;font-size: 28px;color: yellow; border: 2px solid white;");
    text_sloi->setAlignment(Qt::AlignCenter);
    text_sloi->setGeometry(950,49,100,50);

    text_zona->setStyleSheet("background: blue;font-size: 16px;color: yellow; border: 2px solid white;");
    text_zona->setAlignment(Qt::AlignCenter);
    text_zona->setGeometry(950,149,100,30);

    ICOS->setStyleSheet("font: bold 22px;color: yellow;");
    ICOS->setAlignment(Qt::AlignCenter);
    ICOS->setGeometry(20,5,100,30);

    regim_l->setStyleSheet("font:bold 18px;color: yellow;");
    regim_l->setAlignment(Qt::AlignCenter);
    regim_l->setGeometry(20,35,100,30);

    timer->start(40);

    regim->setObjectName("regim");
    regim->setStyleSheet("#regim {color: yellow;}");
    regim->setText("Ручной");
    regim->setGeometry(20,55,100,50);
    regim->setAlignment(Qt::AlignCenter);

    MOC->setObjectName("regim");
    MOC->setStyleSheet("#regim {background: blue;color: yellow; border: 2px solid white; }");
    MOC->setGeometry(1490,1100,105,30);
    MOC->setAlignment(Qt::AlignCenter);

    date->setObjectName("regim");
    date->setStyleSheet("#regim {font:bold 16px;background: blue;color: yellow; border: 2px solid white; }");
    date->setGeometry(1490,1135,105,60);
    date->setAlignment(Qt::AlignCenter);

    QFont font;
    font.setPixelSize(20);
    regim->setFont(font);

    connect(scan_um,        SIGNAL(needUpadateData()), this,  SLOT(Update_graph_UM()));
    connect(scan,           SIGNAL(needUpadateData()), this,  SLOT(Update_graph_KU()));
    connect(miliampermeter, SIGNAL(needUpadateData()), this,  SLOT(Update_graph_Amper()));
    connect(timer,          SIGNAL(timeout()),         this,  SLOT(timeToUpdtae()));
    connect(timer_draw,     SIGNAL(timeout()),         this,  SLOT(timeToDraw()));

    grabKeyboard();

    if(!usb_mko_pribor1m->start()){
        QMessageBox msgBox;
        msgBox.setText("Плата обмена канала МКО с Прибором 1М\n не найдена");
        msgBox.exec();
        panel_error->setError_1M(true);
    }

}
void pult_3m1_main_class::timeToDraw(){

 //   listScreen[0]->grabWindow(0).toImage();
   //timer_draw->start(2);


}


void pult_3m1_main_class::update_down_panel(){

}

pult_3m1_main_class::~pult_3m1_main_class()
{


}
void pult_3m1_main_class::Update_graph_Amper(){
    miliampermeter->SetAngleStrelka(Amper);
}

void pult_3m1_main_class::paintEvent(QPaintEvent *){

    /*if(scan->getPosikRegim() ==  scanning_class::Krug){
        QPainter painter;
        painter.begin(this);
        painter.drawImage(0,0,screen_background);
        painter.end();
    }*/
}
void pult_3m1_main_class::Update_graph_UM(void){
    scan_um->setUM(UM);
}

void pult_3m1_main_class::Update_graph_KU(void){
 //   zahvat_angle+=0.9;
 //   vizir_angle+=0.3;
 //   if(zahvat_angle > 359.9999) zahvat_angle =0;
  //  if(vizir_angle > 359.9999) vizir_angle =0;

    scan->setVizir(-vizir_angle);
    scan->setZahvat(zahvat_angle);
    scan->SetDalnost(Dalnost);

   // timer_draw->start(5);
   // grabScreen->GrabScreen();
   // listScreen[0]->grabWindow(0).toImage();
}

void pult_3m1_main_class::timeToUpdtae(){

    date->setText((time->currentDateTime()).toString("HH:mm:ss\ndd:MM:yy"));

   // panel_antena->setKU(vizir_angle);
   // panel_antena->setUM(UM);
    panel_vizir->setDalnost(Dalnost);
    panel_vizir->setPeleng(-zahvat_angle);
    panel_param->setDlanost(Dalnost);
    // listScreen[1]->grabWindow(0).toImage();

   // zahvat_angle+=0.9;
   // vizir_angle+=0.3;
}

void pult_3m1_main_class::keyPressEvent(QKeyEvent *event){


    switch (event->key()) {
    case Qt::Key_Space:
        if(side == left){
            anim1->setStartValue(QRect(0,0,1600,1080));
            anim1->setEndValue(QRect(1600,0,1600,1080));
            anim1->start();

            anim2->setStartValue(QRect(1600,0,1600,1080));
            anim2->setEndValue(QRect(0,0,1920,1080));
            anim2->start();

            side = right;
        }else{
            // showNormal();
            anim1->setStartValue(QRect(1600,0,1600,1080));
            anim1->setEndValue(QRect(0,0,1600,1200));
            anim1->start();

            anim2->setStartValue(QRect(0,0,1600,1080));
            anim2->setEndValue(QRect(1600,0,1600,1080));
            anim2->start();
            side = left;
        }
        break;
    case Qt::Key_S:
        scan->setPoiskRegim(pult::Sektor);
        regim->setText("Секторный");
        break;
    case Qt::Key_C:
        scan->setPoiskRegim(pult::Krug);
        regim->setText("Круговой");

        break;
    case Qt::Key_A:
        scan->setPoiskRegim(pult::Regim_1A);
        regim->setText("1А");
        break;
    case Qt::Key_1:
        scan      ->SetScaleScan   (pult::scale_0_15);
        panel_RLS ->SetDalnostScale(pult::scale_0_15);
        scan_um   ->SetScaleScan   (pult::scale_0_15);
        break;
    case Qt::Key_2:
        scan      ->SetScaleScan   (pult::scale_0_30);
        panel_RLS ->SetDalnostScale(pult::scale_0_30);
        scan_um   ->SetScaleScan   (pult::scale_0_30);
        break;
    case Qt::Key_3:
        scan      ->SetScaleScan   (pult::scale_15_45);
        panel_RLS ->SetDalnostScale(pult::scale_15_45);
        scan_um   ->SetScaleScan   (pult::scale_15_45);
        break;

    case Qt::Key_Left:
        zahvat_angle+=0.9;

        break;
    case Qt::Key_Right:
        zahvat_angle-=0.9;

        break;
    case Qt::Key_Q:
        vizir_angle+=0.3;
        break;
    case Qt::Key_E:
        vizir_angle-=0.3;
        break;

    case Qt::Key_Up:
        Dalnost+=100;
        break;
    case Qt::Key_Down:
        Dalnost-=100;
        break;

    case Qt::Key_PageUp:
        UM+=0.3;
        break;
    case Qt::Key_PageDown:
        UM-=0.3;
        break;
    case Qt::Key_Plus:
        Amper+=0.4;
        break;
    case Qt::Key_Minus:
        Amper-=0.4;
        break;
    case Qt::Key_F1:

        break;
    case Qt::Key_P:
        PlayStarted();
        break;
    case Qt::Key_R:
        grabScreen->StartRecord();
        break;
    case Qt::Key_T:
       // ThreadGrabScreen->stop();
        grabScreen->StopRecord();
        break;
    default:
        break;
    }
}
QImage pult_3m1_main_class::DrawBackground(void){
    QPixmap map(1096,1096);
    QPainter painter;
    map.fill(QColor(0x00,0x80,0x00));

    QPen pen;

    QFont font;
    pen.setWidth(2);
    painter.begin(&map);

    painter.setRenderHint(QPainter::TextAntialiasing,true);
    painter.setRenderHint((QPainter::Antialiasing),true);
    pen.setWidth(2);
    pen.setColor(Qt::white);

    painter.setPen(pen);
    painter.drawRect(0,0,1600,1200);
    painter.translate(548,548);
    painter.drawEllipse(QPointF(0,0),512,512);
    painter.drawEllipse(QPointF(0,0),526,526);

    font.setPixelSize(18);
    font.setBold(true);
    painter.setFont(font);

    for (int j = 0;j<360;j=j+90)
    {
        painter.rotate(j);
        QString angle;
        QRectF rect(-60,-545,120,20);
        if(j == 0){
            angle = "N";
            painter.drawText(rect,Qt::AlignCenter,angle);
        }else if (j==90) {
            angle = "E";
            painter.drawText(rect,Qt::AlignCenter,angle);
        }
        else if(j==180)
        {
            angle = "S";
            painter.drawText(rect,Qt::AlignCenter,angle);

        }else if(j==270){
            angle = "W";
            painter.drawText(rect,Qt::AlignCenter,angle);
        }
        else
            painter.drawText(rect,Qt::AlignCenter,angle.number(j/0.06));

        painter.rotate(-j);
    }
    for (float j = 0;j<360;j=j+360/36)
    {
        painter.rotate(j);
        painter.drawLine(0,-512,0,-525);
        painter.rotate(-j);
    }

    painter.end();
    return map.toImage();
}

void pult_3m1_main_class::PlayStarted(void){

}


