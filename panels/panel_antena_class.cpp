#include "panel_antena_class.h"

panel_antena_class::panel_antena_class(int posX, int PosY,QWidget *parent) : QFrame(parent)

{
    this->setGeometry(posX,PosY,250,100); // установка местополжения и размеров
    this->setObjectName("panel");         // присвоение имени объекту
    this->setStyleSheet("#panel { border: 2px solid white; background: blue;color: white }");// установка синего фона, белого цвета,белая окантовка


   // QLabel *stat_KU = new QLabel("КУ = ",this); // создание надписи
    QLabel *title   = new QLabel("Координаты антенны",this); // создание надписи
   // QLabel *stat_UM = new QLabel("УМ =",this);    // создание надписи


  /*  text_KU   = new QLabel(this); // текст текущего КУ
    text_UM  = new QLabel(this); // текст текущего УМ

    stat_KU ->setStyleSheet(style_antena); // установка синего фона, белого цвета, 16 размер текста

    stat_UM ->setStyleSheet(style_antena); // установка синего фона, белого цвета, 16 размер текста
    text_KU ->setStyleSheet(style_antena); // установка синего фона, белого цвета, 16 размер текста
    text_UM ->setStyleSheet(style_antena); // установка синего фона, белого цвета, 16 размер текста

    stat_KU ->setAlignment(Qt::AlignCenter);// установка выравенивания по центру

    stat_UM ->setAlignment(Qt::AlignCenter);// установка выравенивания по центру
    text_KU ->setAlignment(Qt::AlignCenter);// установка выравенивания по центру
    text_UM ->setAlignment(Qt::AlignCenter);// установка выравенивания по центру


    stat_KU ->setGeometry(15,40,50,20);  // установка местополжения и размеров
    text_KU ->setGeometry(60,40,185,20); // установка местополжения и размеров
    stat_UM ->setGeometry(15,70,50,20); // установка местополжения и размеров
    text_UM ->setGeometry(60,70,185,20); // установка местополжения и размеров

    setKU(305); // устанока начальнго значения КУ
    setUM(10);  // устанока начальнго значения УМ*/
    title   ->setGeometry(0,0,250,30);   // установка местополжения и размеров
    title   ->setStyleSheet(style_antena_title); // установка синего фона, белого цвета, 16 размер текста
    title   ->setAlignment(Qt::AlignCenter);// установка выравенивания по центру
}

panel_antena_class::~panel_antena_class(){
    delete text_KU;
    delete text_UM;

}

//---------------устновка текста дальности------------------

void panel_antena_class::setKU(float angle){
    if(angle < 0.0) angle+=359.9999;
    text_KU->setText(QString::number(angle/0.06,10,1)+" тд ( "+QString::number(angle,10,1) + "º)");
}
//---------------устновка текста пеленга--------------------
void panel_antena_class::setUM(float angle){
    text_UM->setText(QString::number(angle/0.06,10,1)+" тд ( "+QString::number(angle,10,1) + "º)");
    if(angle <0.0) text_UM->setStyleSheet("QLabel {color : red; font-size: 21px}");
    else text_UM->setStyleSheet("QLabel {color : yellow; font-size: 21px}");
}



