#include "tou_keyboard_class.h"


tou_keyboard_class::tou_keyboard_class(QWidget *parent, int X, int Y)
    : QWidget(parent)
{
    setGeometry(X,Y,1024,768);
  //  Q_INIT_RESOURCE(image);

    setObjectName("TOUwidget");
    QString str = "#TOUwidget {background-color: #FEF9EC}";
    setStyleSheet(str);

    memset(&but_flag,0x00,sizeof(but_flag));


    strbutChecked =            "QPushButton:checked {background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0.1, stop:0 #BC8F8F, stop:1 #FFE4C4);\
                                           border: 3px solid #5A9157;border-radius:7px;font-family:Times, sans-serif; font-size:20px }\
                                    QPushButton {background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0.1, stop:0 #FFEBCD, stop:1 #FFE4C4);\
                                           border: 3px solid #5F4D18;border-radius:7px; font-family:Times, sans-serif; font-size:20px}";
    strbutPressed =            "QPushButton:pressed {background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0.1, stop:0 #BC8F8F, stop:1 #FFE4C4);\
                                               border: 3px solid #5A9157;border-radius:7px;font-family:Times, sans-serif; font-size:20px }\
                                        QPushButton {background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0.1, stop:0 #FFEBCD, stop:1 #FFE4C4);\
                                               border: 3px solid #5F4D18;border-radius:7px; font-family:Times, sans-serif; font-size:20px}";

    strlab =            "QLabel {font-family:Times, sans-serif;\
                                           font-size:20px} ";

    strlab1 =           "QLabel {font-family:Times, sans-serif;\
                                           font-size:15px} ";

    stringTOP =         "QPushButton:pressed {image:url(:/IMAGE/toppressed.png);\
                                           border: 3px solid #5A9157;border-radius:7px}\
                                    QPushButton {image:url(:/IMAGE/top.png); border: 2px solid #5F4D18;\
                                           border-radius:7px}";

    stringLEFT =        "QPushButton:pressed {image:url(:/IMAGE/leftpressed.png);\
                                           border: 3px solid #5A9157;border-radius:7px}\
                                    QPushButton {image:url(:/IMAGE/left.png); border: 2px solid #5F4D18;\
                                           border-radius:7px}";

    stringRIGHT =       "QPushButton:pressed {image:url(:/IMAGE/rightpressed.png);\
                                           border: 3px solid #5A9157;border-radius:7px}\
                                    QPushButton {image:url(:/IMAGE/right.png); border: 2px solid #5F4D18;\
                                           border-radius:7px}";

    stringDOWN =        "QPushButton:pressed {image:url(:/IMAGE/downpressed.png);\
                                           border: 3px solid #5A9157;border-radius:7px}\
                                    QPushButton {image:url(:/IMAGE/down.png); border: 2px solid #5F4D18;\
                                           border-radius:7px}";

    stringCURS =        "QPushButton:checked {image:url(:/IMAGE/curspressed.png);\
                                           border: 3px solid #5A9157;border-radius:7px}\
                                    QPushButton {image:url(:/IMAGE/curs.png); border: 2px solid #5F4D18;\
                                           border-radius:7px}";

    LICHT =             "QPushButton:pressed {background-color: #00FF00; border: 3px solid black;border-radius:20px}\
                                    QPushButton {border: 3px solid black;\
                                           border-radius:20px; background-color: #FF0000}";

    stringBright =      "QPushButton:pressed {image:url(:/IMAGE/brightpressed.png);\
                                           border: 3px solid #5A9157;border-radius:7px; font-family:Times, sans-serif; font-size:20px}\
                                    QPushButton {image:url(:/IMAGE/bright.png); border: 2px solid #5F4D18;\
                                           border-radius:7px; font-family:Times, sans-serif; font-size:20px}";

    stringBLWT =        "QPushButton:checked {image:url(:/IMAGE/WBpressed.png);\
                                           border: 3px solid #5A9157;border-radius:7px}\
                                    QPushButton {image:url(:/IMAGE/WB.png); border: 2px solid #5F4D18;\
                                           border-radius:7px}";


    stringCONTRAST =    "QPushButton:pressed {image:url(:/IMAGE/contrastpressed.png);\
                                           border: 3px solid #5A9157;border-radius:7px; font-family:Times, sans-serif; font-size:20px}\
                                    QPushButton {image:url(:/IMAGE/contrast.png); border: 2px solid #5F4D18;\
                                           border-radius:7px; font-family:Times, sans-serif; font-size:20px; }";

    stringFOCUS =       "QPushButton:pressed {image:url(:/IMAGE/focuspressed.png);\
                                           border: 3px solid #5A9157;border-radius:7px;font-family:Times, sans-serif; font-size:20px}\
                                    QPushButton {image:url(:/IMAGE/focus.png); border: 2px solid #5F4D18;\
                                           border-radius:7px;font-family:Times, sans-serif; font-size:20px}";

    InitLabel();
    InitPushButton();

    connect(TOU,            SIGNAL(clicked(bool)), this, SLOT(slotTOU()));
    connect(LD,             SIGNAL(clicked()), this, SLOT(slotLD()));

    connect(K,              SIGNAL(clicked()), this, SLOT(slotK()));
    connect(P,              SIGNAL(clicked()), this, SLOT(slotP()));
    connect(F2,             SIGNAL(clicked()), this, SLOT(slotF2()));
    connect(T,              SIGNAL(clicked()), this, SLOT(slotT()));
    connect(LEFT,           SIGNAL(clicked()), this, SLOT(slotLEFT()));
    connect(O,              SIGNAL(clicked()), this, SLOT(slotO()));
    connect(RIGHT,          SIGNAL(clicked()), this, SLOT(slotRIGHT()));
    connect(F1,             SIGNAL(clicked()), this, SLOT(slotF1()));
    connect(DOWN,           SIGNAL(clicked()), this, SLOT(slotDOWN()));
    connect(B,              SIGNAL(clicked()), this, SLOT(slotB()));

    connect(LIGHT,          SIGNAL(clicked()), this, SLOT(slotLIGHT()));
    connect(LD1,            SIGNAL(clicked()), this, SLOT(slotLD1()));
    connect(LD2,            SIGNAL(clicked()), this, SLOT(slotLD2()));

    connect(A,              SIGNAL(clicked()), this, SLOT(slotA()));
    connect(CUR,            SIGNAL(clicked()), this, SLOT(slotCUR()));
    connect(BLACKWHITE,     SIGNAL(clicked()), this, SLOT(slotBLACKWHITE()));
    connect(TVSH,           SIGNAL(clicked()), this, SLOT(slotTVSH()));
    connect(TVY,            SIGNAL(clicked()), this, SLOT(slotTVY()));

    connect(BRIGHTPLUS,     SIGNAL(clicked()), this, SLOT(slotBRIGHTPLUS()));
    connect(BRIGHTMINUS,    SIGNAL(clicked()), this, SLOT(slotBRIGHTMINUS()));
    connect(CONTRASTPLUS,   SIGNAL(clicked()), this, SLOT(slotCONTRASTPLUS()));
    connect(CONTRASTMINUS,  SIGNAL(clicked()), this, SLOT(slotCONTRASTMINUS()));
    connect(FOCUSPLUS,      SIGNAL(clicked()), this, SLOT(slotFOCUSPLUS()));
    connect(FOCUSMINUS,     SIGNAL(clicked()), this, SLOT(slotFOCUSMINUS()));
    connect(C,              SIGNAL(clicked()), this, SLOT(slotC()));
    connect(ONE,            SIGNAL(clicked()), this, SLOT(slotONE()));
    connect(TWO,            SIGNAL(clicked()), this, SLOT(slotTWO()));

    connect(MC,             SIGNAL(clicked()), this, SLOT(slotMC()));            //2
    connect(VC,             SIGNAL(clicked()), this, SLOT(slotVC()));
    connect(RA,             SIGNAL(clicked()), this, SLOT(slotRA()));
    connect(TEHR,           SIGNAL(clicked()), this, SLOT(slotTEHR()));

    connect(CU1,            SIGNAL(clicked()), this, SLOT(slotCU1()));           //3
    connect(CU2,            SIGNAL(clicked()), this, SLOT(slotCU2()));

}

void tou_keyboard_class::InitLabel()
{
    NAME            = new QLabel("УПРАВЛЕНИЕ ТОУ",this);                //1
    Electropitanie  = new QLabel("ЭЛЕКТРОПИТАНИЕ",this);
    RASRESH         = new QLabel("РАЗРЕШЕНИЕ",this);
    IMAGE           = new QLabel("ИЗОБРАЖЕНИЕ",this);
    BRIGH           = new QLabel("ЯРКОСТЬ",this);
    CONTRAST        = new QLabel("КОНТРАСТ",this);
    FOCUSIR         = new QLabel("ФОКУСИРОВКА",this);
    TV              = new QLabel("ТВ",this);
    ANS             = new QLabel("ОТВЕТ  ПО\nУКАЗАНИЮ",this);           //2
    CU              = new QLabel("ВЫБОР\nВНЕШНЕГО ЦУ", this);           //3
    NAME            ->setGeometry(250, 30, 300,  30);                   //1
    Electropitanie  ->setGeometry(80, 90, 140,  20);
    RASRESH         ->setGeometry(340, 90, 100,  20);
    IMAGE           ->setGeometry(460, 230, 110,  20);
    BRIGH           ->setGeometry(550, 270, 100,  20);
    CONTRAST        ->setGeometry(550, 380, 100,  20);
    FOCUSIR         ->setGeometry(540, 490, 110,  20);
    TV              ->setGeometry(730,230,100,20);

    ANS             ->setGeometry(840,30,110,50);                       //2

    CU              ->setGeometry(500,660,200,50);                      //3

    ArrayLab1 << Electropitanie << RASRESH << IMAGE << BRIGH << CONTRAST << FOCUSIR << TV;

    for (int i = 0; i < ArrayLab1.size(); i++)
    {
        ArrayLab1[i]->setStyleSheet(strlab1);
    }

    NAME            ->setStyleSheet(strlab);
    ANS             ->setStyleSheet(strlab);
    CU              ->setStyleSheet(strlab);
    CU              ->setAlignment(Qt::AlignCenter);
}

void tou_keyboard_class::InitPushButton()
{
    TOU             = new QPushButton("ТОУ",this);              //1
    LD              = new QPushButton("ЛД",this);
    K               = new QPushButton("К",this);
    P               = new QPushButton("Р",this);
    F2              = new QPushButton("Ф2",this);
    TOP             = new QPushButton(this);
    T               = new QPushButton("Т",this);
    LEFT            = new QPushButton(this);
    O               = new QPushButton("O",this);
    RIGHT           = new QPushButton(this);
    F1              = new QPushButton("Ф1",this);
    DOWN            = new QPushButton(this);
    B               = new QPushButton("В",this);
    LIGHT           = new QPushButton(this);
    LD1             = new QPushButton("ЛД1",this);
    LD2             = new QPushButton("ЛД2",this);
    A               = new QPushButton("A", this);
    CUR             = new QPushButton(this);
    BLACKWHITE      = new QPushButton(this);
    TVSH            = new QPushButton("ТВШ",this);
    TVY             = new QPushButton("ТВУ",this);
    BRIGHTPLUS      = new QPushButton("\n\n+",this);
    BRIGHTMINUS     = new QPushButton("\n\n-",this);
    CONTRASTPLUS    = new QPushButton("\n\n+",this);
    CONTRASTMINUS   = new QPushButton("\n\n-",this);
    FOCUSMINUS      = new QPushButton("\n\n+",this);
    FOCUSPLUS       = new QPushButton("\n\n-",this);
    C               = new QPushButton("С",this);
    ONE             = new QPushButton("1",this);
    TWO             = new QPushButton("2", this);

    MC              = new QPushButton("МЦ",this);                   //2
    VC              = new QPushButton("ВЦ", this);
    RA              = new QPushButton("Раб.\n автон.", this);
    TEHR            = new QPushButton("Техн.\nрежим", this);

    CU1             = new QPushButton("ЦУ1", this);                 //3
    CU2             = new QPushButton("ЦУ2", this);

    TOU             ->setGeometry(50, 110, 80, 80);                 //1
    LD              ->setGeometry(150,110,80,80);
    K               ->setGeometry(50,240,80,80);
    P               ->setGeometry(140,240,80,80);
    F2              ->setGeometry(15,330,80,80);
    TOP             ->setGeometry(105,330,80,80);
    T               ->setGeometry(195,330,80,80);
    LEFT            ->setGeometry(15,420,80,80);
    O               ->setGeometry(105,420,80,80);
    RIGHT           ->setGeometry(195,420,80,80);
    F1              ->setGeometry(15,510,80,80);
    DOWN            ->setGeometry(105,510,80,80);
    B               ->setGeometry(195,510,80,80);
    LIGHT           ->setGeometry(350,130,40,40);
    LD1             ->setGeometry(460,110,80,80);
    LD2             ->setGeometry(590,110,80,80);
    A               ->setGeometry(349,290,80,80);
    CUR             ->setGeometry(310,400,80,80);
    BLACKWHITE      ->setGeometry(400,400,80,80);
    TVSH            ->setGeometry(310,510,80,80);
    TVY             ->setGeometry(400,510,80,80);
    BRIGHTPLUS      ->setGeometry(500,290,80,80);
    BRIGHTMINUS     ->setGeometry(590,290,80,80);
    CONTRASTPLUS    ->setGeometry(500,400,80,80);
    CONTRASTMINUS   ->setGeometry(590,400,80,80);
    FOCUSPLUS       ->setGeometry(500,510,80,80);
    FOCUSMINUS      ->setGeometry(590,510,80,80);
    C               ->setGeometry(700,290,80,80);
    ONE             ->setGeometry(700,400,80,80);
    TWO             ->setGeometry(700,510,80,80);

    MC              ->setGeometry(840,110,100,80);                  //2
    VC              ->setGeometry(840,200,100,80);
    RA              ->setGeometry(840,290,100,80);
    TEHR            ->setGeometry(840,380,100,80);

    CU1             ->setGeometry(710,650,100,70);                  //3
    CU2             ->setGeometry(840,650,100,70);

    ArrayBut1 << TOU << LD << K << P << F2 << T << O << F1 << B << LD1 << LD2 << A << TVSH << TVY << C << ONE << TWO
              << TOP << LEFT << RIGHT << DOWN << LIGHT << CUR << BLACKWHITE << BRIGHTPLUS << BRIGHTMINUS << CONTRASTPLUS
              << CONTRASTMINUS << FOCUSPLUS << FOCUSMINUS << MC << VC << RA << TEHR << CU1 << CU2;

    for (int i = 0; i < ArrayBut1.size(); i++)
    {
        ArrayBut1[i]->setStyleSheet(strbutChecked);
        ArrayBut1[i]->setCheckable(true);
        //ArrayBut1[i]->setChecked(true);
    }

    TOP             ->setStyleSheet(stringTOP);
    LEFT            ->setStyleSheet(stringLEFT);
    RIGHT           ->setStyleSheet(stringRIGHT);
    DOWN            ->setStyleSheet(stringDOWN);
    LIGHT           ->setStyleSheet(LICHT);
    CUR             ->setStyleSheet(stringCURS);
    BLACKWHITE      ->setStyleSheet(stringBLWT);
    BRIGHTPLUS      ->setStyleSheet(stringBright);
    BRIGHTMINUS     ->setStyleSheet(stringBright);
    CONTRASTPLUS    ->setStyleSheet(stringCONTRAST);
    CONTRASTMINUS   ->setStyleSheet(stringCONTRAST);
    FOCUSPLUS       ->setStyleSheet(stringFOCUS);
    FOCUSMINUS      ->setStyleSheet(stringFOCUS);
    K               ->setStyleSheet(strbutPressed);
    P               ->setStyleSheet(strbutPressed);
    F2              ->setStyleSheet(strbutPressed);
    T               ->setStyleSheet(strbutPressed);
    O               ->setStyleSheet(strbutPressed);
    F1              ->setStyleSheet(strbutPressed);
    B               ->setStyleSheet(strbutPressed);

    TVSH->setChecked(true);

}

void tou_keyboard_class::slotTOU()
{
    if (TOU->isChecked())
    {
        but_flag.STR_TOU = true;
    }
    else
    {
        but_flag.STR_TOU = false;
    }
}

void tou_keyboard_class::slotLD()
{
    if (LD->isChecked())
    {
        but_flag.STR_LD = true;
    }
    else
    {
        but_flag.STR_LD = false;
    }
    emit signalChange();
}

void tou_keyboard_class::slotK(void)
{
    if (K->isDown())
    {
        but_flag.STR_K = true;
    }
    else
    {
        but_flag.STR_K = false;
    }
    emit signalChange();
}

void tou_keyboard_class::slotP(void)
{
    if (P->isDown())
    {
        but_flag.STR_P = true;
    }
    else
    {
        but_flag.STR_P = false;
    }
    emit signalChange();
}

void tou_keyboard_class::slotF2(void)
{
    if (F2->isDown())
    {
        but_flag.STR_F2 = true;
    }
    else
    {
        but_flag.STR_F2 = false;
    }
    emit signalChange();
}

void tou_keyboard_class::slotTOP(void)
{
    if (TOP->isDown())
    {
        but_flag.STR_TOP = true;
    }
    else
    {
        but_flag.STR_TOP = false;
    }
    emit signalChange();
}

void tou_keyboard_class::slotT(void)
{
    if (T->isDown())
    {
        but_flag.STR_T = true;
    }
    else
    {
        but_flag.STR_T = false;
    }
    emit signalChange();
}

void tou_keyboard_class::slotLEFT(void)
{
    if (LEFT->isDown())
    {
        but_flag.STR_LEFT = true;
    }
    else
    {
        but_flag.STR_LEFT = false;
    }
    emit signalChange();
}

void tou_keyboard_class::slotO(void)
{
    if (O->isDown())
    {
        but_flag.STR_O = true;
    }
    else
    {
        but_flag.STR_O = false;
    }
    emit signalChange();
}

void tou_keyboard_class::slotRIGHT(void)
{
    if (RIGHT->isDown())
    {
        but_flag.STR_RIGHT = true;
    }
    else
    {
        but_flag.STR_RIGHT = false;
    }
    emit signalChange();
}

void tou_keyboard_class::slotF1(void)
{
    if (F1->isDown())
    {
        but_flag.STR_F1 = true;
    }
    else
    {
        but_flag.STR_F1 = false;
    }
    emit signalChange();
}

void tou_keyboard_class::slotDOWN(void)
{
    if (DOWN->isDown())
    {
        but_flag.STR_DOWN = true;
    }
    else
    {
        but_flag.STR_DOWN = false;
    }
    emit signalChange();
}

void tou_keyboard_class::slotB(void)
{
    if (B->isDown())
    {
        but_flag.STR_B = true;
    }
    else
    {
        but_flag.STR_B = false;
    }
    emit signalChange();
}

void tou_keyboard_class::slotLIGHT(void)
{
    if (LIGHT->isDown())
    {
        but_flag.STR_LIGHT = true;
    }
    else
    {
        but_flag.STR_LIGHT = false;
    }
    emit signalChange();
}

void tou_keyboard_class::slotLD1(void)
{
    if (LD1->isChecked())
    {
        LD2->setChecked(false);
        but_flag.STR_LD1 = true;
    }
    else
    {
        LD1->setChecked(true);
        but_flag.STR_LD1 = false;
    }
    emit signalChange();
}

void tou_keyboard_class::slotLD2(void)
{
    if (LD2->isChecked())
    {
        LD1->setChecked(false);
        but_flag.STR_LD2 = true;
    }
    else
    {
        LD2->setChecked(true);
        but_flag.STR_LD2 = false;
    }
    emit signalChange();
}

void tou_keyboard_class::slotA(void)
{
    if (A->isChecked())
    {
        but_flag.STR_A = true;
    }
    else
    {
        but_flag.STR_A = false;
    }
    emit signalChange();
}

void tou_keyboard_class::slotCUR(void)
{
    if (CUR->isChecked())
    {
        but_flag.STR_CUR = true;
    }
    else
    {
        but_flag.STR_CUR = false;
    }
    emit signalChange();
}

void tou_keyboard_class::slotBLACKWHITE(void)
{
    if (BLACKWHITE->isChecked())
    {
        but_flag.STR_BLACKWHITE = true;
    }
    else
    {
        but_flag.STR_BLACKWHITE = false;
    }
    emit signalChange();
}

void tou_keyboard_class::slotTVSH(void)
{
    if (TVSH->isChecked())
    {
        TVY->setChecked(false);
        but_flag.STR_TVSH = true;
    }
    else
    {
        TVSH->setChecked(true);
        but_flag.STR_TVSH = false;
    }
    emit signalChange();
}

void tou_keyboard_class::slotTVY(void)
{
    if (TVY->isChecked())
    {
        TVSH->setChecked(false);
        but_flag.STR_TVY = true;
    }
    else
    {
        TVY->setChecked(true);
        but_flag.STR_TVY = false;
    }
    emit signalChange();
}

void tou_keyboard_class::slotBRIGHTPLUS(void)
{
    if (BRIGHTPLUS->isDown())
    {
        but_flag.STR_BRIGHTPLUS = true;
    }
    else
    {
        but_flag.STR_BRIGHTPLUS = false;
    }
    emit signalChange();
}

void tou_keyboard_class::slotBRIGHTMINUS(void)
{
    if (BRIGHTMINUS->isDown())
    {
        but_flag.STR_BRIGHTMINUS = true;
    }
    else
    {
        but_flag.STR_BRIGHTMINUS = false;
    }
    emit signalChange();
}

void tou_keyboard_class::slotCONTRASTPLUS(void)
{
    if (CONTRASTPLUS->isDown())
    {
        but_flag.STR_CONTRASTPLUS = true;
    }
    else
    {
        but_flag.STR_CONTRASTPLUS = false;
    }
    emit signalChange();
}

void tou_keyboard_class::slotCONTRASTMINUS(void)
{
    if (CONTRASTMINUS->isDown())
    {
        but_flag.STR_CONTRASTMINUS = true;
    }
    else
    {
        but_flag.STR_CONTRASTMINUS = false;
    }
    emit signalChange();
}

void tou_keyboard_class::slotFOCUSPLUS(void)
{
    if (FOCUSPLUS->isDown())
    {
        but_flag.STR_FOCUSPLUS = true;
    }
    else
    {
        but_flag.STR_FOCUSPLUS = false;
    }
    emit signalChange();
}

void tou_keyboard_class::slotFOCUSMINUS(void)
{
    if (FOCUSMINUS->isDown())
    {
        but_flag.STR_FOCUSMINUS = true;
    }
    else
    {
        but_flag.STR_FOCUSMINUS = false;
    }
    emit signalChange();
}

void tou_keyboard_class::slotC(void)
{
    if (C->isChecked())
    {
        TWO->setChecked(false);
        ONE->setChecked(false);
        but_flag.STR_C = true;
    }
    else
    {
        C->setChecked(true);
        but_flag.STR_C = false;
    }
    emit signalChange();
}

void tou_keyboard_class::slotONE(void)
{

    if (ONE->isChecked())
    {
        TWO->setChecked(false);
        C->setChecked(false);
        but_flag.STR_ONE = true;
    }
    else
    {
        ONE->setChecked(true);
        but_flag.STR_ONE = false;
    }
    emit signalChange();
}

void tou_keyboard_class::slotTWO(void)
{
    if (TWO->isChecked())
    {
        ONE->setChecked(false);
        C->setChecked(false);
        but_flag.STR_TWO = true;
    }
    else
    {
        TWO->setChecked(true);
        but_flag.STR_TWO = false;
    }
    emit signalChange();
}

void tou_keyboard_class::slotMC(void)
{
    if (MC->isDown() == false)
    {
        MC->setDown(true);
        but_flag.STR_MC = true;
    }
    else
    {
        MC->setDown(false);
        but_flag.STR_MC = false;
    }
    emit signalChange();
}

void tou_keyboard_class::slotVC(void)
{
    if (VC->isDown())
    {
        but_flag.STR_VC = true;
    }
    else
    {
        but_flag.STR_VC = false;
    }
    emit signalChange();
}

void tou_keyboard_class::slotRA(void)
{
    if (RA->isDown())
    {
        but_flag.STR_RA = true;
    }
    else
    {
        but_flag.STR_RA = false;
    }
    emit signalChange();
}

void tou_keyboard_class::slotTEHR(void)
{
    if (TEHR->isDown())
    {
        but_flag.STR_TEHR = true;
    }
    else
    {
        but_flag.STR_TEHR = false;
    }
    emit signalChange();
}

void tou_keyboard_class::slotCU1(void)
{
    if (CU1->isChecked())
    {
        CU2->setChecked(false);
        but_flag.STR_CU1 = true;
    }
    else
    {
        CU1->setChecked(true);
        but_flag.STR_CU1 = false;
    }
    emit signalChange();
}

void tou_keyboard_class::slotCU2(void)
{
    if (CU2->isChecked())
    {
        CU1->setChecked(false);
        but_flag.STR_CU2 = true;
    }
    else
    {
        CU2->setChecked(true);
        but_flag.STR_CU2 = false;
    }
    emit signalChange();
}

void tou_keyboard_class::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
    painter.drawRoundedRect(QRect(2,10,800,600),5,5);       //1
    painter.drawRoundedRect(QRect(40,80,200,120),5,5);      //Электропитание
    painter.drawRoundedRect(QRect(300,80,380,120),5,5);     //Разрешение
    painter.drawRoundedRect(QRect(5,220,280,380),5,5);      //Панель упрвления
    painter.drawRoundedRect(QRect(300,220,380,380),5,5);    //Изображение
    painter.drawRoundedRect(QRect(495,270,180,105),5,5);    //Яркость
    painter.drawRoundedRect(QRect(495,380,180,105),5,5);    //Контраст
    painter.drawRoundedRect(QRect(495,490,180,105),5,5);    //Фокусировка
    painter.drawRoundedRect(QRect(690,220,100,380),5,5);    //ТВ
    painter.drawRoundedRect(QRect(812,10,164,600),5,5);     //2
    painter.drawRoundedRect(QRect(490,625,486,120),5,5);    //3
}

tou_keyboard_class::~tou_keyboard_class()
{
    delete NAME;

}
