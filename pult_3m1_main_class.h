#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPalette>
#include <QLabel>



#include <QTimer>
#include <QKeyEvent>
#include <QDebug>
#include <scannig/scanning_class.h>
#include <QtMath>
#include <QThread>
#include <QFontDatabase>
#include <QPropertyAnimation>
#include <QScreen>
#include <QGuiApplication>
#include <QApplication>
#include <QMessageBox>

#include "scannig/um_scannig_class.h"
#include "widgets/autotrack_dalnost_class.h"
#include "panels/panel_vizir_class.h"
#include "panels/panel_antena_class.h"
#include "panels/panel_param_class.h"
#include "panels/panel_error_class.h"
#include "panels/panel_RLS_class.h"
#include "widgets/miliampermeter_class.h"
#include "video/videowidget.h"
#include "usb/linux_usb_class.h"
#include "widgets/tou_keyboard_class.h"
#include "video/grab_screen_class.h"
#include "opengl/pult.h"
#include "usb/usb_mko_pribor1m_class.h"



//#include "ippcore.h"

class pult_3m1_main_class : public QWidget
{
    Q_OBJECT

public:
    pult_3m1_main_class(QWidget *parent= 0);
    ~pult_3m1_main_class();

    scanning_class               *scan;
    panel_vizir_class            *panel_vizir;
    panel_antena_class           *panel_antena;
    panel_param_class            *panel_param;
    panel_error_class            *panel_error;
    panel_RLS_class              *panel_RLS;
    UM_scannig_class             *scan_um;
    autotrack_dalnost_class      *autotrack_dalnost;
    miliampermeter_class         *miliampermeter;
    tou_keyboard_class           *tou_keyboard;
    grab_screen_class            *grabScreen;
    usb_mko_Pribor1M_class       *usb_mko_pribor1m;


    QLabel             *regim;
    QLabel             *date;
    QLabel             *MOC;
    QDateTime          *time;
    QTimer             *timer;
    QTimer             *timer_draw;
    QLabel             *text_sloi;
    QLabel             *text_zona;
    VideoWidget        *video;
    QPropertyAnimation *anim1;
    QPropertyAnimation *anim2;

    Data_in_BC123_S Data_in_BC123;


private:
    enum{
        left,
        right
    };

    int height;
    int width;
    bool side;
    float vizir_angle;
    float zahvat_angle;
    float kurs_angle;
    float Dalnost;
    float UM;
    float Amper;
    QThread *ThreadGrabScreen;
    QList<QScreen*> listScreen;
    QImage screen_background;


    QImage DrawBackground(void);

    void PlayStarted(void);

protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
    virtual void  keyPressEvent(QKeyEvent *event);

signals:

    void RecStarted(void);

public slots:

    void timeToUpdtae(void);
    void timeToDraw(void);

    void update_down_panel(void);
    void Update_graph_UM(void);
    void Update_graph_KU(void);
    void Update_graph_Amper(void);

};

#endif // WIDGET_H
