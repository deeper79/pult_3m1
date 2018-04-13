#include "draw_texture_class.h"

draw_texture_class::draw_texture_class()
{

}

QImage draw_texture_class::TextureAutoTrak(){
    QPixmap map(500,280);
    QPainter painter;
    QPen pen;
    QFont font;
    map.fill(QColor(0,0,0xFF));
    painter.begin(&map);
    font.setPixelSize(17);

    pen.setWidth(2);
    pen.setColor(Qt::white);

    painter.setPen(pen);
    painter.setFont(font);
    painter.setRenderHint((QPainter::Antialiasing),true);
    painter.drawRect(1,1,499,278);//

    painter.drawRect(271,29,218,218); // зона автосопровождения
    painter.drawRect(271,4,218,26);
    painter.drawText(QRect(271,4,218,26),Qt::AlignCenter,"Ошибка автосопровождения");
    painter.drawRect(11,29,238,218);  // зона дальности
    painter.drawRect(11,4,238,26);
    painter.drawText(QRect(11,4,238,26),Qt::AlignCenter,"Точная дальность");


    //---------------Рисование зоны автосопровождения------------------------------
    pen.setColor(Qt::white);
    painter.save();
    pen.setWidthF(1.5);
    painter.setPen(pen);
    painter.translate(380,138);
    painter.drawLine(-100,0,100,0);
    painter.drawLine(0,-100,0,100);

    for(int i=1;i<6;i++){
        painter.drawLine(-i*18,-5,-i*18,5);// растановка меток на оси КУ 1дел = 18pix = 3тд = 0.17 тд/pix
        painter.drawLine(i*18,-5,i*18,5);
        painter.drawLine(-5,-18*i,5,-18*i); // растановка меток на оси УМ 1дел = 18pix = 3тд = 0.17 тд/pix
        painter.drawLine(-5,18*i,5,18*i);
    }
    painter.drawText(-100,100,"1 дел. = 3тд");

    pen.setColor(Qt::red);
    QBrush brush;
    brush.setColor(Qt::red);
    brush.setStyle(Qt::SolidPattern);

    painter.setPen(pen);
    painter.setBrush(brush);

    painter.restore();

    //-------------------------------------------------------------------------------------------

    //---------------Рисование зоны дальности------------------------------
    pen.setWidthF(1.5);
     pen.setColor(Qt::white);
    painter.setPen(pen);
    painter.translate(130,225);
    painter.drawLine(0,0,0,-190);// ось дальности
    painter.drawLine(-105,0,105,0);// ось дальности

    //-------------------------------------------------------------------------------------------
    for(int i=1;i<7;i++){
        painter.drawLine(-i*17,-5,-i*17,5);// растановка меток на оси КУ 1дел = 17pix = 3тд = 0.17 тд/pix
        painter.drawLine(i*17,-5,i*17,5);
        painter.drawLine(-5,-27*i,5,-27*i); // растановка меток на оси УМ 1дел = 25pix = 3тд = 0.17 тд/pix
    }
    painter.drawText(-100,20,"1 дел. = 100м");
    painter.end();
    map.toImage().save("errpr.jpg");
    return map.toImage().mirrored();
}
QImage draw_texture_class::TextureMiliampermeter(){

    QPixmap map(170,150);
    QPainter painter;
    map.fill(QColor(0,0x00,0xFF));

    QPen pen;
    QBrush brush;

    pen.setWidth(2);
    painter.begin(&map);

    painter.setRenderHint(QPainter::TextAntialiasing,true);
    painter.setRenderHint((QPainter::Antialiasing),true);

    painter.save();

    pen.setColor(Qt::black);

    painter.setPen(pen);

    painter.setBrush(Qt::white);

    painter.translate(85,150);
    painter.drawPie(QRect(-115,-115,230,230),45*16,90*16);

    brush.setColor(Qt::blue);
    brush.setStyle(Qt::SolidPattern);
    pen.setColor(Qt::blue);
    painter.setBrush(brush);
    painter.setPen(pen);
    painter.drawPie(QRect(-30,-30,60,60),45*16,90*16);

    painter.setPen(Qt::black);
    painter.drawArc(QRect(-85,-85,170,170),50*16,82*16);

    for(int i=-3;i<3;i++){
        painter.rotate(14*i+7);
        painter.drawText(QRect(-8,-105,16,12),Qt::AlignCenter,QString::number((i+3)*10,0,0));
        painter.drawLine(0,-85,0,-90);
        painter.rotate(-14*i-7);
    }
    pen.setWidth(10);
    pen.setColor(Qt::red);
    painter.setPen(pen);

    painter.drawArc(QRect(-65,-65,130,130),50*16,23*16);

    pen.setWidth(10);
    pen.setColor(Qt::green);
    painter.setPen(pen);

    painter.drawArc(QRect(-65,-65,130,130),80*16,23*16);

    pen.setWidth(10);
    pen.setColor(Qt::blue);
    painter.setPen(pen);

    painter.drawArc(QRect(-65,-65,130,130),110*16,20*16);

    pen.setWidth(2);
    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.drawText(-10,-40,"мА");
    brush.setColor(Qt::red);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);

    painter.restore();
    pen.setWidth(2);
    pen.setColor(Qt::white);
    painter.setPen(pen);
    painter.drawRect(2,2,167,147);
    painter.drawRect(2,2,170,20);

    painter.drawText(QRect(0,0,167,25),Qt::AlignCenter,"Ток магнитрона");
    painter.end();

    return map.toImage().mirrored();
}
QImage draw_texture_class::TextureUM(int Dalnost){
    QPixmap map(512,400);
    QPainter painter;
    map.fill(QColor(0,0,0xFF));

    QPen pen;

    QFont font;
    pen.setWidth(2);
    painter.begin(&map);
    painter.setRenderHint(QPainter::TextAntialiasing,true);
    painter.setRenderHint(QPainter::Antialiasing,true);


   // painter.setRenderHint((QPainter::Antialiasing),true); // вкючение сглаживания

    pen.setColor(QColor(255,255,255,255));
    font.setPixelSize(14);
    //--------отрисовка бордера
    painter.setPen(pen);
    painter.setFont(font);
    painter.drawRect(1,1,511,399);

    //---------------отрисовка осей координат
    painter.translate(23,319); // перенос начала системы координат
    float temp;

    switch (Dalnost) {
    case pult::scale_0_15:
        temp = 2.5;
        break;
    case pult::scale_0_30:
         temp = 5.0;
        break;
    case pult::scale_15_45:
        temp = 7.5;

        break;
    default:
        temp =0;
        break;
    }

    int radius =65;
    for(int i=0;i<7;i++){
        painter.drawArc(QRect(-radius*i,-radius*i,2*radius*i,2*radius*i),270*16,180*16); // рисование окружностей по дальнотси
        if(!(i%2))  // рисуем только четный
            painter.drawText((radius)*i+5,15,QString::number(temp*(i),10,0));  // подпись под осью дальности

    }

    painter.drawText(-20,-95, "10");  // подпись под осью высоты
    painter.drawText(-20,-195,"20");  // подпись под осью высоты

    painter.drawLine(0,70,0,-280); //ось высоты
    painter.drawLine(-20,0,450,0); //ось дальности

    //стрелка оси высоты и подпись
    painter.save();
    painter.translate(0,-280);
    painter.drawLine(0,0,-5,10);
    painter.drawLine(0,0, 5,10);
    painter.drawText(-20,5,"Н,");
    painter.drawText(-20,20,"км");
    painter.restore();

    //стрелка оси дальности и подпись
    painter.save();
    painter.translate(450,0);
    painter.drawLine(0,0,-10,5);
    painter.drawLine(0,0,-10,-5);
    painter.drawText(-5,15,"Д,км");
    painter.restore();

    painter.save();
    painter.rotate(-14);
    painter.drawLine(0,0,420,0);
    painter.drawText(430,0,"18 º");
    painter.restore();
    painter.rotate(-29);
    painter.drawLine(0,0,420,0);
    painter.drawText(430,0,"36 º");


    painter.end();
    //  map.toImage().save("UM.jpg");

    return map.toImage().mirrored();

}
QImage draw_texture_class::TextureSectorIndikator(){
    QPixmap map(260,260);
    QPainter painter;
    QBrush brush;
    map.fill(QColor(0,0x0,0x80,0xFF));

    QPen pen;

    QFont font;
    font.setPixelSize(16);
    pen.setWidth(2);
    painter.begin(&map);

    painter.setRenderHint(QPainter::TextAntialiasing,true);
    painter.setRenderHint((QPainter::Antialiasing),true);
    painter.setFont(font);

    // Вспомогательные линии
    pen.setWidth(2);
    pen.setColor(QColor(128,128,128,200));

    brush.setColor(Qt::black);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.translate(130,130);
    painter.drawEllipse(QRect(-105,-105,105*2,105*2));
    painter.setBrush(Qt::NoBrush);
    pen.setColor(Qt::white);
    painter.setPen(pen);
    painter.drawRect(-130,-130,260,260);
 //   painter.drawLine(-130,0,260,0);
  //  painter.drawLine(0,-130,0,260);

    painter.drawEllipse(QRect(-105,-105,105*2,105*2));

    painter.drawText(QRect(  -8,-122,16,16), Qt::AlignCenter,"N");
    painter.drawText(QRect(  -8, 111,16,16), Qt::AlignCenter,"S");
    painter.drawText(QRect(-125, -8,16,16),  Qt::AlignCenter,"W");
    painter.drawText(QRect( 109, -8,16,16),  Qt::AlignCenter,"E");

    painter.end();

    return map.toImage().mirrored();

}

QImage draw_texture_class::TextureKrug(int regim){
    QPixmap map(1096,1096);
    QPainter painter;
    map.fill(QColor(0x00,0x00,0x60,0x00));

    QPen pen;

    QFont font;
    pen.setWidth(2);
    painter.begin(&map);

    painter.setRenderHint(QPainter::TextAntialiasing,true);
    painter.setRenderHint((QPainter::Antialiasing),true);

    pen.setColor(QColor(128,128,128,100));
    painter.setPen(pen);
    painter.save();

    // painter.drawRect(40,40,1024,1024);
    painter.translate(548,548);
    font.setPixelSize(12);
    painter.setFont(font);


    for(int i=5000;i<30000;i = i+5000){
        painter.drawEllipse(QPointF(0,0),(int)(i*(512.0/30000.0)),(int)(i*(512.0/30000.0)));
    }
    int temp;
    if(regim == 0) temp = 15;
    else temp = 6;

    for(int i=0;i<360;i=i+temp){
        painter.rotate(i);
        painter.drawLine(0,0,-512,0);
        painter.rotate(-i);
    }
    painter.restore();
    pen.setColor(Qt::white);
    pen.setWidth(2);

    painter.setPen(pen);
    painter.translate(548,548);
    painter.drawEllipse(QPointF(0,0),512,512);
    painter.drawEllipse(QPointF(0,0),526,526);
    //painter.translate(512,512);
    if(regim == 0) temp = 15;
    else temp = 6;
    for (float j = 0;j<360;j=j+temp)
    {
        painter.rotate(j);
        painter.drawLine(0,-512,0,-525);
        painter.rotate(-j);
    }


    font.setPixelSize(18);
    font.setBold(true);
    painter.setFont(font);

    if(regim == 0) temp = 30;
    else temp = 6;

    for (int j = 0;j<360;j=j+temp)
    {
        painter.rotate(j);
        QString angle;
        QRectF rect(-60,-545,120,20);
        if(j == 0){
            angle = "N";
            painter.drawText(rect,Qt::AlignCenter,angle);
        }else if (j==90) {
            angle = "E";
            painter.drawText(rect,Qt::AlignCenter,angle);
        }
        else if(j==180)
        {
            angle = "S";
            painter.drawText(rect,Qt::AlignCenter,angle);


        }else if(j==270){
            angle = "W";
            painter.drawText(rect,Qt::AlignCenter,angle);
        }
        else
            painter.drawText(rect,Qt::AlignCenter,angle.number(j/0.06,10,0));

        painter.rotate(-j);
    }
    //map.toImage().save("test.jpg");
   // pen.setColor(QColor(0x00,0x00,0x00,0xff));

   // painter.drawEllipse(QPointF(0,0),128,128);

    painter.end();
    return map.toImage().mirrored();

}

QImage draw_texture_class::DrawScreenRLS_IndicatorA(int Dalnst){

    QPixmap map(1096,1096);
    QPainter painter;
    map.fill(QColor(0,0,0,0x00));

    QPen pen;
    pen.setColor(Qt::white);

    QFont font;
    pen.setWidth(2);
    painter.begin(&map);
    painter.translate(36,36);

    painter.setRenderHint(QPainter::TextAntialiasing,true);
    painter.setRenderHint((QPainter::Antialiasing),true);

    painter.setPen(pen);
    painter.setFont(font);
    switch (Dalnst) {
    case pult::scale_0_15:
        painter.drawText(QRect(10,860,100,30),Qt::AlignCenter,"0");
        painter.drawText(QRect(10,375,100,30),Qt::AlignCenter,"10");
        painter.drawText(QRect(10,620,100,30),Qt::AlignCenter,"5");
        painter.drawText(QRect(10,120,100,30),Qt::AlignCenter,"Д,км");
        break;
    case pult::scale_0_30:
        painter.drawText(QRect(10,860,100,30),Qt::AlignCenter,"0");
        painter.drawText(QRect(10,375,100,30),Qt::AlignCenter,"20");
        painter.drawText(QRect(10,620,100,30),Qt::AlignCenter,"10");
        painter.drawText(QRect(10,120,100,30),Qt::AlignCenter,"Д,км");
        break;
    case pult::scale_15_45:
        painter.drawText(QRect(10,120,100,30),Qt::AlignCenter,"Д,км");
        painter.drawText(QRect(10,375,100,30),Qt::AlignCenter,"35");
        painter.drawText(QRect(10,620,100,30),Qt::AlignCenter,"25");
        painter.drawText(QRect(10,860,100,30),Qt::AlignCenter,"15");

        break;
    default:
        break;
    }
    int temp = -3000;
    painter.drawRect(72,147,880,730);
    for(int i=0;i<13;i++){
        painter.drawText(QRect(0.146666667*i*500+47,880,50,30),Qt::AlignCenter,QString::number(temp)); // pix=880/6000
        painter.drawLine(0.146666667*(i+1)*500 -1,880,0.146666667*(i+1)*500 -1,875); // pix=880/6000
        temp+=500;
    }
    painter.drawText(QRect(965,880,70,30),Qt::AlignCenter,"КУ,т.д.");

    pen.setColor(QColor(255,255,255,40));
    painter.setPen(pen);

    for(int i=0;i<13;i++){
        painter.drawLine(0.146666667*(i+1)*500 -1,147,0.146666667*(i+1)*500 -1,877); // pix=880/6000
        temp+=500;
    }

    painter.drawLine(72,389,952,389); // pix=880/6000
    painter.drawLine(72,635,952,635); // pix=880/6000


    painter.end();
    return map.toImage().mirrored();

}

