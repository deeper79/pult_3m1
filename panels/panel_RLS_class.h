#ifndef PANEL_RLS_H
#define PANEL_RLS_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <QLabel>
#include <QGridLayout>
#include <QPaintEvent>
#include <QPushButton>


class panel_RLS_class: public QFrame
{
    Q_OBJECT
public:
    explicit panel_RLS_class(int posX = 0,int PosY =0,QWidget *parent = Q_NULLPTR);
    ~panel_RLS_class();
    inline void setCuMain(bool in){
        button_CU_main->setChecked(in);
    }

    inline void setCuRez(bool in){
        button_CU_main->setChecked(in);
    }

    inline void setD(bool in){
        button_D->setChecked(in);
    }

    inline void setSPC(bool in){
        button_SPC->setChecked(in);
    }

    inline void setUppHigh(bool in){
        button_UPP_high->setChecked(in);
    }

    inline void setUppReady(bool in){
        button_UPP_ready->setChecked(in);
    }

    inline void setUppSigReady(bool in){
        button_UPP_ready->setChecked(in);
    }

    inline void setUppSVCH(bool in){
        button_UPP_SVCH->setChecked(in);
    }

    inline void setUppAPCH(bool in){
        button_UPP_APCH->setChecked(in);
    }
    void SetDalnostScale(int scale);

    enum{
        scale_0_15,
        scale_0_30,
        scale_15_45
    };


private:
#define style_button_RLS "#button {background: qradialgradient(cx:0, cy:0, radius: 1,fx:0.5, fy:0.5, stop:0 white, stop:1 darkGray);border-radius: 12px}\
                          #button:checked {background: qradialgradient(cx:0, cy:0, radius: 1,fx:0.5, fy:0.5, stop:0 white, stop:1 green);border-radius: 12px}"
#define style_RLS_title "background: blue;color: yellow;font-size: 18px;border: 2px solid white"
#define style_RLS "background: blue;color: yellow;font-size: 21px"
#define style_RLS_littal "background: blue;color: yellow;font-size: 12px"

    QPushButton *button_CU_main;
    QPushButton *button_CU_rez;
    QPushButton *button_D;
    QPushButton *button_SPC;
    QPushButton *button_UPP_high;
    QPushButton *button_UPP_ready;
    QPushButton *button_UPP_sig_ready;
    QPushButton *button_UPP_SVCH;
    QPushButton *button_UPP_APCH;
    QLabel      *text_regim;
    QLabel      *text_D;
    QLabel      *text_PR;
    QLabel      *text_Huv;
    QLabel      *text_Hf;



protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
};

#endif // PANEL_ANTENA_H
