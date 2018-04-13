#include "autotrack_dalnost_class.h"
autotrack_dalnost_class::autotrack_dalnost_class(QWidget *parent,int posX,int posY):QOpenGLWidget(parent),
    Error_KU(0),Error_UM(0)
{
    setGeometry(posX,posY,500,240);
    image = new opengl_draw_class;
    image->SetTextureImage(draw_texture_class::TextureAutoTrak());
    image->setSizeGlView(500,240);
    image->SetGeometry(0,0,500,240);

}

void autotrack_dalnost_class::initializeGL(){
    initializeOpenGLFunctions();
   if(image != NULL ) image->init();
}

void autotrack_dalnost_class::resizeGL(int nWidth, int nHeight){
    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
}

void autotrack_dalnost_class::paintGL(){
    glClearColor(0.0, 0.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(image->inited()) image->Draw();

    QPainter painter;
    QPen pen;
    QFont font;
    QBrush brush;

    pen.setColor(QColor(255,255,255,255));
    font.setPixelSize(12);

    pen.setWidth(2);
    painter.begin(this);
    painter.save();
    painter.translate(380,120);
    pen.setColor(Qt::red);

    brush.setColor(Qt::red);
    brush.setStyle(Qt::SolidPattern);

    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawEllipse(QPointF(0,0),3,3);//Рисование точки ошибки
    painter.restore();
    painter.translate(130,205);

    pen.setColor(Qt::white);

    painter.setPen(pen);
    painter.end();
    update();
}
autotrack_dalnost_class::~autotrack_dalnost_class(){
    delete timer;
}
