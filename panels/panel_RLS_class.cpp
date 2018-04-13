#include "panel_RLS_class.h"

panel_RLS_class::panel_RLS_class(int posX, int PosY,QWidget *parent) : QFrame(parent)

{
    this->setGeometry(posX,PosY,500,325); // установка местополжения и размеров
    this->setObjectName("panel");         // присвоение имени объекту
    this->setStyleSheet("#panel { border: 2px solid white; background: blue;color: white }");// установка синего фона, белого цвета,белая окантовка

    text_regim        = new QLabel("АВТОНОМНЫЙ",this);
    text_D            = new QLabel("0 - 30 км",this);
    text_PR           = new QLabel("ОТКЛ",this);
    text_Huv          = new QLabel("1000 м",this);
    text_Hf           = new QLabel("2000 м",this);

    QLabel *title   = new QLabel("Режим работы РЛС",this); // создание надписи
    title->setStyleSheet(style_RLS_title);                 // установка синего фона, белого цвета, 16 размер текста
    title->setAlignment(Qt::AlignCenter);                  // установка выравенивания по центру
    title->setGeometry(0,0,width(),30);


    QLabel *regim   = new QLabel("Режим          :",this); // создание надписи
    regim->setStyleSheet(style_RLS);                 // установка синего фона, белого цвета, 16 размер текста
    regim->setAlignment(Qt::AlignCenter);                  // установка выравенивания по центру
    regim->setGeometry(10,40,125,30);

    text_regim->setStyleSheet(style_RLS);                 // установка синего фона, белого цвета, 16 размер текста
    text_regim->setAlignment(Qt::AlignCenter);                  // установка выравенивания по центру
    text_regim->setGeometry(145,40,155,30);



    QLabel *dist  = new QLabel("Дист. Д         :",this); // создание надписи
    dist->setStyleSheet(style_RLS);                 // установка синего фона, белого цвета, 16 размер текста
    dist->setAlignment(Qt::AlignCenter);                  // установка выравенивания по центру
    dist->setGeometry(10,80,125,30);


    text_D->setStyleSheet(style_RLS);                 // установка синего фона, белого цвета, 16 размер текста
    text_D->setAlignment(Qt::AlignCenter);                  // установка выравенивания по центру
    text_D->setGeometry(115,80,125,30);

    QLabel *PR  = new QLabel("Режим ПР     :",this); // создание надписи
    PR->setStyleSheet(style_RLS);                 // установка синего фона, белого цвета, 16 размер текста
    PR->setAlignment(Qt::AlignCenter);                  // установка выравенивания по центру
    PR->setGeometry(10,120,125,30);


    text_PR->setStyleSheet(style_RLS);                 // установка синего фона, белого цвета, 16 размер текста
    text_PR->setAlignment(Qt::AlignCenter);                  // установка выравенивания по центру
    text_PR->setGeometry(135,120,55,30);

    QLabel *Hf  = new QLabel("Нф = ",this); // создание надписи
    Hf->setStyleSheet(style_RLS);                 // установка синего фона, белого цвета, 16 размер текста
    Hf->setAlignment(Qt::AlignCenter);                  // установка выравенивания по центру
    Hf->setGeometry(280,150,60,25);

    text_Hf->setStyleSheet(style_RLS);                 // установка синего фона, белого цвета, 16 размер текста
    text_Hf->setAlignment(Qt::AlignCenter);                  // установка выравенивания по центру
    text_Hf->setGeometry(335,150,70,25);


    QLabel *Huv  = new QLabel("Нув = ",this); // создание надписи
    Huv->setStyleSheet(style_RLS);                 // установка синего фона, белого цвета, 16 размер текста
    Huv->setAlignment(Qt::AlignCenter);                  // установка выравнивания по центру
    Huv->setGeometry(60,150,60,25);



    text_Huv->setStyleSheet(style_RLS);                 // установка синего фона, белого цвета, 16 размер текста
    text_Huv->setAlignment(Qt::AlignCenter);                  // установка выравнивания по центру
    text_Huv->setGeometry(115,150,70,25);


    QLabel *Perehvat  = new QLabel("Перехват",this); // создание надписи
    Perehvat->setStyleSheet(style_RLS);                 // установка синего фона, белого цвета, 16 размер текста
    Perehvat->setAlignment(Qt::AlignCenter);                  // установка выравнивания по центру
    Perehvat->setGeometry(60,192,100,25);

    QLabel *UPP  = new QLabel("УПП",this); // создание надписи
    UPP->setStyleSheet(style_RLS);                 // установка синего фона, белого цвета, 16 размер текста
    UPP->setAlignment(Qt::AlignCenter);                  // установка выравнивания по центру
    UPP->setGeometry(300,192,100,25);

    QLabel *CU  = new QLabel("ЦУ",this); // создание надписи
    CU->setStyleSheet(style_RLS);                 // установка синего фона, белого цвета, 16 размер текста
    CU->setAlignment(Qt::AlignCenter);                  // установка выравнивания по центру
    CU->setGeometry(25,220,30,25);

    QLabel *D  = new QLabel("по Д",this); // создание надписи
    D->setStyleSheet(style_RLS);                 // установка синего фона, белого цвета, 16 размер текста
    D->setAlignment(Qt::AlignCenter);                  // установка выравнивания по центру
    D->setGeometry(65,220,50,25);

    QLabel *SPC  = new QLabel("СПЦ",this); // создание надписи
    SPC->setStyleSheet(style_RLS);                 // установка синего фона, белого цвета, 16 размер текста
    SPC->setAlignment(Qt::AlignCenter);                  // установка выравнивания по центру
    SPC->setGeometry(120,220,50,25);

    QLabel *CU_main  = new QLabel("осн",this); // создание надписи
    CU_main->setStyleSheet(style_RLS_littal);                 // установка синего фона, белого цвета, 16 размер текста
    CU_main->setAlignment(Qt::AlignCenter);                  // установка выравнивания по центру
    CU_main->setGeometry(8,270,30,25);


    QLabel *CU_rez  = new QLabel("рез",this); // создание надписи
    CU_rez->setStyleSheet(style_RLS_littal);                 // установка синего фона, белого цвета, 16 размер текста
    CU_rez->setAlignment(Qt::AlignCenter);                  // установка выравнивания по центру
    CU_rez->setGeometry(38,270,30,25);

    QLabel *UPP_main  = new QLabel("выс",this); // создание надписи
    UPP_main->setStyleSheet(style_RLS_littal);                 // установка синего фона, белого цвета, 16 размер текста
    UPP_main->setAlignment(Qt::AlignCenter);                  // установка выравнивания по центру
    UPP_main->setGeometry(248,270,30,25);

    QLabel *UPP_ready  = new QLabel("готов",this); // создание надписи
    UPP_ready->setStyleSheet(style_RLS_littal);                 // установка синего фона, белого цвета, 16 размер текста
    UPP_ready->setAlignment(Qt::AlignCenter);                  // установка выравнивания по центру
    UPP_ready->setGeometry(296,270,35,25);

    QLabel *UPP_sig  = new QLabel("сигн.\nраб.",this); // создание надписи
    UPP_sig->setStyleSheet(style_RLS_littal);                 // установка синего фона, белого цвета, 16 размер текста
    UPP_sig->setAlignment(Qt::AlignCenter);                  // установка выравнивания по центру
    UPP_sig->setGeometry(344,270,35,45);

    QLabel *UPP_SVCH  = new QLabel("Пробой\nСВЧ",this); // создание надписи
    UPP_SVCH->setStyleSheet(style_RLS_littal);                 // установка синего фона, белого цвета, 16 размер текста
    UPP_SVCH->setAlignment(Qt::AlignCenter);                  // установка выравнивания по центру
    UPP_SVCH->setGeometry(382,270,60,45);

    QLabel *UPP_APCH  = new QLabel("АПЧ",this); // создание надписи
    UPP_APCH->setStyleSheet(style_RLS_littal);                 // установка синего фона, белого цвета, 16 размер текста
    UPP_APCH->setAlignment(Qt::AlignCenter);                  // установка выравнивания по центру
    UPP_APCH->setGeometry(437,270,35,45);


    button_CU_main    = new QPushButton(this);
    button_CU_rez     = new QPushButton(this);
    button_D          = new QPushButton(this);
    button_SPC        = new QPushButton(this);
    button_UPP_high   = new QPushButton(this);
    button_UPP_ready  = new QPushButton(this);
    button_UPP_sig_ready = new QPushButton(this);
    button_UPP_SVCH   = new QPushButton(this);
    button_UPP_APCH   = new QPushButton(this);




    QVector<QPushButton *> buttons;
    buttons << button_CU_main << button_CU_rez << button_D << button_SPC << button_UPP_sig_ready <<
               button_UPP_high << button_UPP_ready << button_UPP_SVCH << button_UPP_APCH;

    for(int i=0;i<buttons.size();i++){
        buttons[i]->setObjectName("button");
        buttons[i]->setStyleSheet(style_button_RLS);
        buttons[i]->setCheckable(true);
    }

    button_CU_main->setGeometry(10,250,25,25);
    button_CU_rez->setGeometry(40,250,25,25);
    button_D->setGeometry(80,250,25,25);
    button_SPC->setGeometry(130,250,25,25);
    button_UPP_high->setGeometry(250,250,25,25);
    button_UPP_ready->setGeometry(300,250,25,25);
    button_UPP_sig_ready->setGeometry(350,250,25,25);
    button_UPP_SVCH->setGeometry(400,250,25,25);
    button_UPP_APCH->setGeometry(450,250,25,25);

}

panel_RLS_class::~panel_RLS_class(){
    delete button_CU_main;
    delete button_CU_rez;
    delete button_D  ;
    delete button_SPC ;
    delete button_UPP_high ;
    delete button_UPP_ready  ;
    delete button_UPP_SVCH ;
    delete button_UPP_APCH;
}
void panel_RLS_class::paintEvent(QPaintEvent *){
    QPainter p;
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::white);
    p.begin(this);
    p.setPen(pen);
    p.drawLine(0,190,width(),190);
    p.drawRect(7,246,65,55);
    p.drawRect(245,246,238,70);
    p.end();

}

void panel_RLS_class::SetDalnostScale(int scale){
    switch (scale) {
    case scale_0_15:
        text_D->setText("0 - 15");
        break;
    case scale_0_30:
        text_D->setText("0 - 30");
        break;
    case scale_15_45:
        text_D->setText("15 - 45");

        break;
    default:
        break;
    }
}




