#ifndef UM_SCANNIG_CLASS_H
#define UM_SCANNIG_CLASS_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QLabel>
#include "../opengl/draw_texture_class.h"
#include "../opengl/opengl_draw_class.h"
#include "../opengl/pult.h"

#define style_UM_title "background: blue;color: yellow;font-size: 20px;border: 2px solid white"
//#define radius 50

class UM_scannig_class:public QOpenGLWidget ,protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit UM_scannig_class(QWidget *parent,int posX,int posY);
    inline void setUM(float ang){UM = ang;}
     void SetScaleScan(int scl);

private:
    opengl_draw_class *image;
    opengl_draw_class *vizir;

    int scale;
    float UM;
    float Dalnost;

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int nWidth, int nHeight) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE ;

signals:
    void needUpadateData();

};

#endif // UM_SCANNIG_CLASS_H
