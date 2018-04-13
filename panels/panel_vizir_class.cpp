#include "panel_vizir_class.h"

panel_vizir_class::panel_vizir_class(int posX, int PosY,QWidget *parent) : QFrame(parent)

{
    this->setGeometry(posX,PosY,250,100); // установка местополжения и размеров
    this->setObjectName("panel");         // присвоение имени объекту
    this->setStyleSheet("#panel { border: 2px solid white; background: blue;color: white }");// установка синего фона, белого цвета,белая окантовка


    QLabel *stat_D      = new QLabel("Д = ",this); // создание надписи
    QLabel *title       = new QLabel("Координаты визира",this); // создание надписи
    QLabel *stat_peleng = new QLabel("П =",this);    // создание надписи


    text_Daln   = new QLabel(this); // текст текущей дальности
    text_peleng = new QLabel(this);// текст текущего пеленга

    stat_D      ->setStyleSheet(style_vizir); // установка синего фона, белого цвета, 16 размер текста
    title       ->setStyleSheet(style_title_vizir); // установка синего фона, белого цвета, 16 размер текста
    stat_peleng ->setStyleSheet(style_vizir); // установка синего фона, белого цвета, 16 размер текста
    text_Daln   ->setStyleSheet(style_vizir); // установка синего фона, белого цвета, 16 размер текста
    text_peleng ->setStyleSheet(style_vizir); // установка синего фона, белого цвета, 16 размер текста

    stat_D      ->setAlignment(Qt::AlignCenter);// установка выравенивания по центру
    title       ->setAlignment(Qt::AlignCenter);// установка выравенивания по центру
    stat_peleng ->setAlignment(Qt::AlignCenter);// установка выравенивания по центру
    text_Daln   ->setAlignment(Qt::AlignCenter);// установка выравенивания по центру
    text_peleng ->setAlignment(Qt::AlignCenter);// установка выравенивания по центру

    title       ->setGeometry(0,0,250,30);   // установка местополжения и размеров
    stat_D      ->setGeometry(15,40,40,20);  // установка местополжения и размеров
    text_Daln   ->setGeometry(60,40,185,20); // установка местополжения и размеров
    stat_peleng ->setGeometry(12,70,40,20); // установка местополжения и размеров
    text_peleng ->setGeometry(60,70,185,20); // установка местополжения и размеров

    setDalnost(0); // устанока начальнго значения дальности
    setPeleng(0);  // устанока начальнго значения пеленга
}

panel_vizir_class::~panel_vizir_class(){
    delete text_Daln;
    delete text_peleng;

}

//---------------устновка текста дальности------------------

 void panel_vizir_class::setDalnost(float daln){
    text_Daln->setText(QString::number(daln,10,0)+" м ( "+QString::number(daln*0.00539956803455724,10,1) + " каб.)");
}
//---------------устновка текста пеленга--------------------
void panel_vizir_class::setPeleng(float angle){
    if(angle < 0.0) angle+=359.99999;
    text_peleng->setText(QString::number(angle/0.06,10,0)+" тд ( "+QString::number(angle,10,1) + " º)");
}



