#ifndef PANEL_ERROR_H
#define PANEL_ERROR_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <QLabel>
#include <QGridLayout>
#include <QPaintEvent>
#include <QPushButton>


class panel_error_class: public QFrame
{
    Q_OBJECT
public:
    explicit panel_error_class(int posX = 0,int PosY =0,QWidget *parent = Q_NULLPTR);
    ~panel_error_class();
    inline void setError_3BM(bool in){
        button_3BM->setDown(in);
    }

    inline void setError_2AM(bool in){
        button_2AM->setDown(in);
    }

    inline void setError_2M(bool in){
        button_2M->setDown(in);
    }

    inline void setError_1M(bool in){
        button_1M->setDown(in);
    }

    inline void setError_3M1(bool in){
        button_3M1->setDown(in);
    }

    inline void setError_obmen_1M(bool in){
        error_1M->setDown(in);
    }

    inline void setError_obmen_BC(bool in){
        error_BC->setDown(in);
    }

private:
#define style_button_error "#button {background: qradialgradient(cx:0, cy:0, radius: 1,fx:0.5, fy:0.5, stop:0 white , stop:1 gray );border-radius: 14px}\
                          #button:pressed {background: qradialgradient(cx:0, cy:0, radius: 1,fx:0.5, fy:0.5, stop:0 white, stop:1 red);border-radius: 14px}"
#define style_error_title "background: blue;color: yellow;font-size: 18px;border: 2px solid white"
#define style_error "background: blue;color: yellow;font-size: 18px"

    QPushButton *button_3BM;
    QPushButton *button_2AM;
    QPushButton *button_2M;
    QPushButton *button_1M;
    QPushButton *button_3M1;
    QPushButton *error_BC;
    QPushButton *error_1M;

protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
};

#endif // PANEL_ANTENA_H
