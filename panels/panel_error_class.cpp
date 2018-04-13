#include "panel_error_class.h"

panel_error_class::panel_error_class(int posX, int PosY,QWidget *parent) : QFrame(parent)

{
    this->setGeometry(posX,PosY,400,100); // установка местополжения и размеров
    this->setObjectName("panel");         // присвоение имени объекту
    this->setStyleSheet("#panel { border: 2px solid white; background: blue;color: white }");// установка синего фона, белого цвета,белая окантовка



    QLabel *title   = new QLabel("Неисправности",this); // создание надписи
    QLabel *title1   = new QLabel("Неисп. обмена",this); // создание надписи
    title   ->setStyleSheet(style_error_title);         // установка синего фона, белого цвета, 16 размер текста
    title   ->setAlignment(Qt::AlignCenter);            // установка выравенивания по центру
    title->setGeometry(0,0,250,30);

    title1   ->setStyleSheet(style_error_title);         // установка синего фона, белого цвета, 16 размер текста
    title1   ->setAlignment(Qt::AlignCenter);            // установка выравенивания по центру
    title1->setGeometry(249,0,150,30);



    button_3BM = new QPushButton(this);
    button_2AM = new QPushButton(this);
    button_2M  = new QPushButton(this);
    button_1M  = new QPushButton(this);
    button_3M1 = new QPushButton(this);
    error_1M   = new QPushButton(this);
    error_BC   = new QPushButton(this);


    QVector<QPushButton *> buttons;
    buttons << button_3BM << button_2AM << button_2M << button_1M << button_3M1 << error_1M << error_BC;

    for(int i=0;i<buttons.size();i++){

        buttons[i]->setObjectName("button");
        buttons[i]->setStyleSheet(style_button_error);
    }


    button_3BM->setGeometry(10,40,30,30);
    button_2AM->setGeometry(60,40,30,30);
    button_2M->setGeometry(110,40,30,30);
    button_1M->setGeometry(160,40,30,30);
    button_3M1->setGeometry(210,40,30,30);
    error_1M->setGeometry(280,40,30,30);
    error_BC->setGeometry(330,40,30,30);

    QLabel *label_3BM  = new QLabel("3Б-М",this);
    QLabel *label_2AM  = new QLabel("2А-М",this);
    QLabel *label_2M   = new QLabel("2М",this);
    QLabel *label_1M   = new QLabel("1М",this);
    QLabel *label_3M1  = new QLabel("3М-1",this);
    QLabel *l_error_1M   = new QLabel("1М",this);
    QLabel *l_error_BC  = new QLabel("BC",this);

    label_3BM->setStyleSheet(style_error);
    label_2AM->setStyleSheet(style_error);
    label_2M->setStyleSheet(style_error);
    label_1M->setStyleSheet(style_error);
    label_3M1->setStyleSheet(style_error);
    l_error_1M->setStyleSheet(style_error);
    l_error_BC->setStyleSheet(style_error);


    label_3BM->setAlignment(Qt::AlignCenter);
    label_2AM->setAlignment(Qt::AlignCenter);
    label_2M->setAlignment(Qt::AlignCenter);
    label_1M->setAlignment(Qt::AlignCenter);
    label_3M1->setAlignment(Qt::AlignCenter);

    l_error_1M->setAlignment(Qt::AlignCenter);
    l_error_BC->setAlignment(Qt::AlignCenter);


    label_3BM->setGeometry(5,75,42,20);
    label_2AM->setGeometry(55,75,43,20);
    label_2M->setGeometry(105,75,40,20);
    label_1M->setGeometry(155,75,40,20);
    label_3M1->setGeometry(200,75,43,20);
    l_error_1M->setGeometry(275,75,40,20);
    l_error_BC->setGeometry(325,75,40,20);
    //setError_1M(true);

}

panel_error_class::~panel_error_class(){
    delete button_3BM ;
    delete button_2AM;
    delete button_2M;
    delete button_1M;
    delete button_3M1;



}
void panel_error_class::paintEvent(QPaintEvent *){
    QPainter p;
    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::white);

    p.begin(this);
    p.setPen(pen);
    p.drawLine(249,0,249,height());
    p.end();

}




