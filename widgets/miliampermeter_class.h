#ifndef MILIAMPERMETR_H
#define MILIAMPERMETR_H


#include <QOpenGLWidget>
#include <QVector3D>
#include <QOpenGLFunctions>

#include "../opengl/opengl_draw_class.h"
#include "../opengl/draw_texture_class.h"


class miliampermeter_class : public QOpenGLWidget ,protected QOpenGLFunctions
{
    Q_OBJECT
public:
      explicit miliampermeter_class(QWidget *parent,int posX,int posY);
    ~miliampermeter_class();
   inline void SetAngleStrelka(float angle){
        angle_strelka = angle;
    }

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int nWidth, int nHeight) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE ;

private:

    float angle_strelka;
    opengl_draw_class *image;
    opengl_draw_class *arrow;


signals:
    void needUpadateData();

};

#endif // AUTOTRACK_H
