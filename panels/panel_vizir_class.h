#ifndef PANEL_VIZIR_H
#define PANEL_VIZIR_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <QLabel>
#include <QGridLayout>
#include <QPaintEvent>


class panel_vizir_class: public QFrame
{
    Q_OBJECT
public:
    explicit panel_vizir_class(int posX = 0,int PosY =0,QWidget *parent = Q_NULLPTR);
    ~panel_vizir_class();

     void setDalnost(float daln); // функция установки дальности
     void setPeleng (float angle); // функция установки дальности

private:
#define style_vizir       "background: blue;color: yellow;font-size: 21px"
#define style_title_vizir "background: blue;color: yellow;font-size: 20px;border: 2px solid white"

    QLabel          *text_Daln;
    QLabel          *text_peleng;

};

#endif // PANEL_VIZIR_H
