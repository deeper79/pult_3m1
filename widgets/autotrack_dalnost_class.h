#ifndef AUTOTRACK_DALNOST_H
#define AUTOTRACK_DALNOST_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QOpenGLShader>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include "../opengl/opengl_draw_class.h"
#include "../opengl/draw_texture_class.h"

#define style_dalnost_title "background: blue;color: white;font-size: 18px;border: 2px solid white"

class autotrack_dalnost_class : public QOpenGLWidget ,protected QOpenGLFunctions
{
    Q_OBJECT
public:
      explicit autotrack_dalnost_class(QWidget *parent,int posX,int posY);
    ~autotrack_dalnost_class();

    inline void setErrorAutoKU(int error){
        Error_KU = (float)error/0.176470588;
    }
    inline void setErrorAutoUM(int error){
        Error_UM = (float)error/0.176470588;
    }
    inline void setErrorDaln(QVector<QPointF> data){
        error = data;
    }

private:
    QTimer                *timer;
    int                   Error_KU;
    int                   Error_UM;
    QVector<QPointF>      error;
    QLabel                *IO_label;
    opengl_draw_class     *image;


protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int nWidth, int nHeight) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE ;
};

#endif // AUTOTRACK_H
