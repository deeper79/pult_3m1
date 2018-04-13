#include "miliampermeter_class.h"
miliampermeter_class::miliampermeter_class(QWidget *parent,int posX,int posY)
    :QOpenGLWidget(parent)
{
    setGeometry(posX,posY,170,150);
    image = new opengl_draw_class;
    image->setSizeGlView(170,150);
    image->SetGeometry(0,0,170,150);
    image->SetTextureImage(draw_texture_class::TextureMiliampermeter());


    arrow = new opengl_draw_class;
    arrow->setSizeGlView(170,150);
    arrow->SetGeometry(0,55,170,170);

    arrow->SetCustomVertex(QVector<QVector4D*>() <<  new QVector4D( 0.05, 0.0 , -0.1, 0.0f)
                           <<  new QVector4D(-0.05, 0.0 , -0.1f, 0.0f)
                           <<  new QVector4D( 0.0 , 1.0 , -0.1f, 0.0f));

    arrow->SetColor(QVector4D(0.5,0.0,0.0,1.0));


    QSurfaceFormat*  surf_format = new QSurfaceFormat();
    surf_format->setSamples(4);
    setFormat(*surf_format);

}

void miliampermeter_class::initializeGL(){
    initializeOpenGLFunctions();

    image->init();
    arrow->init();
}

void miliampermeter_class::resizeGL(int nWidth, int nHeight){
    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
}

void miliampermeter_class::paintGL(){
    glClearColor(0.0, 0.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);

    image->Draw();
    arrow->Draw();
    arrow->SetAngleZ(angle_strelka);

    glDisable(GL_DEPTH_TEST);

    update();

    emit needUpadateData();
}

miliampermeter_class::~miliampermeter_class(){

}
