#ifndef PANEL_PARAM_H
#define PANEL_PARAM_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <QLabel>
#include <QGridLayout>
#include <QPaintEvent>


class panel_param_class: public QFrame
{
    Q_OBJECT
public:
    explicit panel_param_class(int posX = 0,int PosY =0,QWidget *parent = Q_NULLPTR);
    explicit panel_param_class(QWidget *parent = Q_NULLPTR);
    ~panel_param_class();

    void setDlanost(int daln);   // функция установки дальности
    inline void setTpar(float time);    // функция установки времени до параметра
    inline void setVc(float Vc);        // функция установки скорости
    inline void setQc(float Qc);        // функция установки курса
    inline void setH(float H);          // функция установки высоты
    inline void setP(float P);          // функция установки хрен знает

private:
#define style_param       "background: blue;color: yellow;font-size: 21px"
#define style_param_title "background: blue;color: yellow;font-size: 18px;border: 2px solid white"

    QLabel           *text_Dalnost; // текст дальности
    QLabel           *text_tpar;    // текст времени до параметра
    QLabel           *text_Vc;      // текст скорости
    QLabel           *text_Qc;      // текст курса
    QLabel           *text_H;       // текст высоты
    QLabel           *text_P;       // текст хрен знает



protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;


};

#endif // PANEL_PARAM_H
