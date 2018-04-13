#include "panel_param_class.h"

panel_param_class::panel_param_class(int posX, int PosY,QWidget *parent) : QFrame(parent)

{
    this->setGeometry(posX,PosY,570,100); // установка местополжения и размеров
    this->setObjectName("panel");         // присвоение имени объекту
    this->setStyleSheet("#panel { border: 2px solid white; background: blue;color: white }");// установка синего фона, белого цвета,белая окантовка

    QLabel *title         = new QLabel("Параметры движения сопровождаемой цели",this); // создание надписи
    QLabel *label_Dalnost = new QLabel("Д = ",this); // создание надписи
    QLabel *label_tpar    = new QLabel("tпар =",this);    // создание надписи
    QLabel *label_Vc      = new QLabel("Vц =",this);    // создание надписи
    QLabel *label_Qc      = new QLabel("Qц =",this);    // создание надписи
    QLabel *label_H       = new QLabel("H =",this);    // создание надписи
    QLabel *label_P       = new QLabel("P =",this);    // создание надписи

    text_Dalnost  = new QLabel(this);// текст текущей дальности до цели
    text_tpar     = new QLabel(this);// текст времени до параметра
    text_Vc       = new QLabel(this);// текст текущей скорости цели
    text_Qc       = new QLabel(this);// текст текущего курса цели
    text_H        = new QLabel(this);// текст текущей высоты цели
    text_P        = new QLabel(this);// текст текущего хрен знает чего?

    QVector<QLabel *> labels;

    labels << title << label_Dalnost << label_tpar << label_Vc << label_Qc // создание массива из QLabel
           << label_H << label_P << text_Dalnost << text_tpar
           << text_Vc << text_Qc << text_H << text_P;

    for(int i=0;i< labels.size();i++){
        labels[i]->setStyleSheet(style_param);    // установка синего фона, белого цвета, 16 размер текста
        labels[i]->setAlignment(Qt::AlignCenter); // установка выравенивания по центру
    }

    title ->setStyleSheet(style_param_title);  // установка синего фона, белого цвета, 16 размер текста
    title ->setGeometry(0,0,width(),30);       // установка местополжения и размеров

    label_Dalnost ->setGeometry(15,40,40,20);  // позиция надписи текущей дальности до цели
    label_tpar    ->setGeometry(15,70,60,20);  // позиция надписи времени до параметра
    label_Vc      ->setGeometry(205,40,50,20); // позиция надписи текущей скорости цели
    label_Qc      ->setGeometry(205,70,50,20); // позиция надписи текущего курса цели
    label_H       ->setGeometry(395,40,40,20); // позиция надписи текущей высоты цели
    label_P       ->setGeometry(395,70,40,20); // позиция надписи текущего хрен знает чего цели

    text_Dalnost ->setGeometry(60,40,80,20);  // позиция текста текущей дальности до цели
    text_tpar    ->setGeometry(80,70,80,20);  // позиция текста текущнго времени до параметра
    text_Vc      ->setGeometry(250,40,90,20); // позиция текста текущей скорости цели
    text_Qc      ->setGeometry(250,70,90,20); // позиция текста текущего курса  цели
    text_H       ->setGeometry(430,40,90,20); // позиция текста текущей высоты цели
    text_P       ->setGeometry(430,70,90,20); // позиция текста текущей хзч  цели



    setDlanost(11330); // устанока начальнго значения дальности
    setTpar(120.1);    // устанока начальнго значения времени до параметра
    setVc(700);        // устанока начальнго значения скорости
    setQc(353.3);      // устанока начальнго значения курса
    setH(8000);        // устанока начальнго значения высоты
    setP(1000);        // устанока начальнго значения хзч


    // setKU(305); // устанока начальнго значения КУ
    // setUM(10);  // устанока начальнго значения УМ
}
panel_param_class::panel_param_class(QWidget *parent) : QFrame(parent){

}

panel_param_class::~panel_param_class(){
    delete text_Dalnost;
    delete text_tpar;
    delete text_Vc;
    delete text_Qc;
    delete text_H;
    delete text_P;

}

//---------------устновка текста дальности------------------

void panel_param_class::setDlanost(int daln){
    text_Dalnost->setText(QString::number(daln,10,0)+" м");
}

//---------------устновка текста времени до параметра-------
inline void panel_param_class::setTpar(float time){
    text_tpar->setText(QString::number(time,10,1)+" c");
}

//---------------устновка текста скорости цели-------
inline void panel_param_class::setVc(float Vc){
    text_Vc->setText(QString::number(Vc,10,1)+" м/c");
}

//---------------устновка текста курса цели-------
inline void panel_param_class::setQc(float Qc){
    text_Qc->setText(QString::number(Qc/0.06,10,1)+" тд");
}

//---------------устновка текста высоты цели-------
inline void panel_param_class::setH(float H){
    text_H->setText(QString::number(H,10,0)+" м");
}

//---------------устновка текста  хрен знает цели-------
inline void panel_param_class::setP(float P){
    text_P->setText(QString::number(P,10,0)+" м");
}

void panel_param_class::paintEvent(QPaintEvent *){
    QPainter p;

    p.begin(this);
    p.setPen(Qt::white);
    p.drawLine(195,0,195,height());
    p.drawLine(385,0,385,height());
    p.end();

}




