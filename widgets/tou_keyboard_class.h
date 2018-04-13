#ifndef TOU_CLASS
#define TOU_CLASS

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QPainter>
#include <QPixmap>
#include <QString>
#include <QPen>
#include <QPointF>
#include <QKeyEvent>
#include <QList>


class tou_keyboard_class : public QWidget
{
    Q_OBJECT


public:
    tou_keyboard_class(QWidget *parent = 0, int X = 150, int Y = 150);
    ~tou_keyboard_class();


    void InitLabel(void);
    void InitPushButton(void);

typedef struct
{

//***************-1-*****************
    //Электропитание
    bool STR_TOU;
    bool STR_LD;

    //ПАНЕЛЬ НАВИГАЦИИ
    bool STR_K;
    bool STR_P;
    bool STR_F2;
    bool STR_TOP;
    bool STR_T;
    bool STR_LEFT;
    bool STR_O;
    bool STR_RIGHT;
    bool STR_F1;
    bool STR_DOWN;
    bool STR_B;

    //РАЗРЕШЕНИЕ
    bool STR_LIGHT;
    bool STR_LD1;
    bool STR_LD2;

    //ИЗОБРАЖЕНИЕ
    bool STR_A;
    bool STR_CUR;
    bool STR_BLACKWHITE;
    bool STR_TVSH;
    bool STR_TVY;
        //ЯРКОСТЬ
    bool STR_BRIGHTPLUS;
    bool STR_BRIGHTMINUS;
        //КОНТРАСТ
    bool STR_CONTRASTPLUS;
    bool STR_CONTRASTMINUS;

        //ФОКУСИРОВКА
    bool STR_FOCUSPLUS;
    bool STR_FOCUSMINUS;

    //ТВ
    bool STR_C;
    bool STR_ONE;
    bool STR_TWO;
//***********************-2-*******************
    //Ответ по указанию
    bool STR_MC;
    bool STR_VC;
    bool STR_RA;
    bool STR_TEHR;
//*************************-3-******************
    bool STR_CU1;
    bool STR_CU2;

}but_flag_S;


private:
    but_flag_S but_flag;

//***************-1-*****************
    QString                 stringCONTRAST;
    QString                 stringFOCUS;
    QString                 strbutPressed;
    QString                 strbutChecked;
    QString                 strlab;
    QString                 strlab1;
    QString                 stringTOP;
    QString                 stringLEFT;
    QString                 stringRIGHT;
    QString                 stringDOWN;
    QString                 stringCURS;
    QString                 LICHT;
    QString                 stringBright;
    QString                 stringBLWT;

    QList<QLabel *>         ArrayLab1;
    QList<QPushButton *>    ArrayBut1;
    //Электропитание
    QLabel                  *Electropitanie;
    QPushButton             *TOU;
    QPushButton             *LD;

    //ПАНЕЛЬ НАВИГАЦИИ
    QPushButton             *K;
    QPushButton             *P;
    QPushButton             *F2;
    QPushButton             *TOP;
    QPushButton             *T;
    QPushButton             *LEFT;
    QPushButton             *O;
    QPushButton             *RIGHT;
    QPushButton             *F1;
    QPushButton             *DOWN;
    QPushButton             *B;

    //РАЗРЕШЕНИЕ
    QPushButton             *LIGHT;
    QPushButton             *LD1;
    QPushButton             *LD2;

    //ИЗОБРАЖЕНИЕ

    QPushButton             *A;
    QPushButton             *CUR;
    QPushButton             *BLACKWHITE;
    QPushButton             *TVSH;
    QPushButton             *TVY;

    QLabel                  *BRIGH;                 //ЯРКОСТЬ
    QPushButton             *BRIGHTPLUS;
    QPushButton             *BRIGHTMINUS;

    QLabel                  *CONTRAST;              //КОНТРАСТ
    QPushButton             *CONTRASTPLUS;
    QPushButton             *CONTRASTMINUS;

    QLabel                  *FOCUSIR;               //ФОКУСИРОВКА
    QPushButton             *FOCUSPLUS;
    QPushButton             *FOCUSMINUS;

    QLabel                  *RASRESH;
    QLabel                  *IMAGE;
    QLabel                  *NAME;

    //ТВ
    QPushButton             *C;
    QPushButton             *ONE;
    QPushButton             *TWO;
    QLabel                  *TV;

//***********************-2-*******************
    //Ответ по указанию
    QLabel                  *ANS;
    QPushButton             *MC;
    QPushButton             *VC;
    QPushButton             *RA;
    QPushButton             *TEHR;

//*************************-3-******************
    QPushButton             *CU1;
    QPushButton             *CU2;
    QLabel                  *CU;

    QPixmap                 map;
//**********************************************
    int MousePosX;
    int MousePosY;
public slots:
    void slotTOU();             //1
    void slotLD();

    void slotK(void);
    void slotP(void);
    void slotF2(void);
    void slotTOP(void);
    void slotT(void);
    void slotLEFT(void);
    void slotO(void);
    void slotRIGHT(void);
    void slotF1(void);
    void slotDOWN(void);
    void slotB(void);

    void slotLIGHT(void);
    void slotLD1(void);
    void slotLD2(void);

    void slotA(void);
    void slotCUR(void);
    void slotBLACKWHITE(void);
    void slotTVSH(void);
    void slotTVY(void);

    void slotBRIGHTPLUS(void);
    void slotBRIGHTMINUS(void);
    void slotCONTRASTPLUS(void);
    void slotCONTRASTMINUS(void);
    void slotFOCUSPLUS(void);
    void slotFOCUSMINUS(void);
    void slotC(void);
    void slotONE(void);
    void slotTWO(void);

    void slotMC(void);          //2
    void slotVC(void);
    void slotRA(void);
    void slotTEHR(void);

    void slotCU1(void);         //3
    void slotCU2(void);

signals:
    void signalChange(void);

protected:
    void paintEvent(QPaintEvent *);

};


#endif // WIDGET_H
