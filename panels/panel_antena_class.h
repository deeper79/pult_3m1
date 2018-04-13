#ifndef PANEL_ANTENA_H
#define PANEL_ANTENA_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <QLabel>
#include <QGridLayout>
#include <QPaintEvent>


class panel_antena_class: public QFrame
{
    Q_OBJECT
public:
    explicit panel_antena_class(int posX = 0,int PosY =0,QWidget *parent = Q_NULLPTR);
    ~panel_antena_class();

    void setKU(float angle);   // функция установки КУ
    void setUM(float angle); // функция установки УМ

private:
#define style_antena       "background: blue;color: yellow;font-size: 21px"
#define style_antena_title "background: blue;color: yellow;font-size: 20px;border: 2px solid white"

    QLabel          *text_KU;
    QLabel          *text_UM;

};

#endif // PANEL_ANTENA_H
