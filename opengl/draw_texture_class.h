#ifndef DRAW_TEXTURE_CLASS_H
#define DRAW_TEXTURE_CLASS_H

#include <QPainter>
#include <QImage>
#include <QPixmap>
#include "pult.h"


class draw_texture_class
{
public:
    draw_texture_class();

    static QImage TextureKurgPoisk(void);
    static QImage TextureAutoTrak(void);
    static QImage TextureMiliampermeter(void);
    static QImage TextureUM(int Dalnost);
    static QImage TextureSectorIndikator(void);
    static QImage TextureKrug(int regim);
    static QImage DrawScreenRLS_IndicatorA(int Dalnst);
};

#endif // DRAW_TEXTURE_CLASS_H
