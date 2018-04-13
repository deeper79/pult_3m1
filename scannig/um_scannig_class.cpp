#include "um_scannig_class.h"

UM_scannig_class::UM_scannig_class(QWidget *parent,int posX,int posY):QOpenGLWidget(parent),scale(0)
{
    setGeometry(posX,posY,512,400);

    QLabel *tittle =new QLabel("Угол места антенного поста",this);
    tittle->setGeometry(0,0,width(),30);
    tittle->setStyleSheet(style_UM_title);
    tittle->setAlignment(Qt::AlignCenter);// установка выравнивание по центру

    UM = 0;

    image = new opengl_draw_class;
    image->setSizeGlView(512,400);
    image->SetGeometry(0,0,512,400);
    image->SetTextureImage(draw_texture_class::TextureUM(pult::scale_0_15));


    vizir = new opengl_draw_class();
    vizir->setSizeGlView(512,400);
    vizir->SetCustomVertex(QVector<QVector4D*>()
                        << new QVector4D( -0.005f, 1.0, -0.1, 0.0f) << new QVector4D( -0.005f, 0.0, -0.1,0.0f) << new QVector4D( 0.005f, 0.0, -0.1,0.0f)
                        << new QVector4D( -0.005f, 1.0, -0.1, 0.0f) << new QVector4D(  0.005f, 0.0, -0.1,0.0f) << new QVector4D( 0.005f, 1.0, -0.1,0.0f));

    vizir->SetGeometry(-233,-80,512,800);
    vizir->SetColor(QVector4D(1.0,1.0,1.0,1.0));


    QSurfaceFormat*  surf_format = new QSurfaceFormat();
    surf_format->setSamples(2);
    setFormat(*surf_format);
}

void UM_scannig_class::initializeGL(){

    initializeOpenGLFunctions();
    image->init();
    vizir->init();
}

void UM_scannig_class::resizeGL(int nWidth, int nHeight){
    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);

}

void UM_scannig_class::paintGL(){

    glClearColor(0.0, 0.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);

    vizir->Draw();
    vizir->SetAngleZ(UM-90);
    image->Draw();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_MULTISAMPLE);
    update();
    emit needUpadateData();
}

void UM_scannig_class::SetScaleScan(int scl){
    image->SetNewTexture(draw_texture_class::TextureUM(scl));
    scale = scl;
}





