#ifndef scanning_class_H
#define scanning_class_H


#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QTimer>
#include <QVector3D>
#include <QMatrix4x4>
#include <QOpenGLFunctions>
#include <QSurfaceFormat>
#include <QOpenGLTexture>
#include <QTime>
#include <QList>
#include <QOpenGLDebugLogger>
#include <QPainter>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QCoreApplication>
#include <QOpenGLDebugMessage>
#include <QtMath>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFramebufferObjectFormat>
#include <QDebug>
#include <QPushButton>
#include <QPixmap>
#include <QLabel>
#include <QScreen>
#include <QtMath>



#include "../opengl/draw_texture_class.h"
#define deltaX 40
#define deltaY 40
#define texel 1.0/1096.0

#include "../opengl/opengl_draw_class.h"
#include "../usb/usb_adc_rls_class.h"



class scanning_class : public QOpenGLWidget ,protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit scanning_class(QWidget *parent,int posX,int posY);
    explicit scanning_class(QWidget *parent,int posX,int posY,int width,int height);

    void SetTimePoslesvech(float time);
    void setPoiskRegim    (int ena);
    void SetScaleScan     (int scl);

    void setKU(float ang){KU = ang;}
    void setVizir(float ang){vizir_angle = ang;}
    void setZahvat(float ang){zahvat_angle = ang;}
    int  getPosikRegim(void) const {return poisk_regim;}
    void SetDalnost(float d) {Dalnost = d;}

    int  GetScaleScan(void) const    {return scale;}


    inline double PointToTexel(int point){
        double out=0;
        if(point>0){
            return out = 1  - texel*point;
        }else{
            return out = -1 - texel*point;
        }
      }
    ~scanning_class();

private:


     opengl_draw_class *sektor_indikator;
     opengl_draw_class *vizir;
     opengl_draw_class *scan;
     opengl_draw_class *scan_back;
     opengl_draw_class *kurs;
     opengl_draw_class *zahvat;
     opengl_draw_class *sector_indicator_line;

   //  usb_adc_rls_class *usb_adc_rls;


    QVector<QVector4D *> init_vertex_vizir(void);
    QVector<QVector4D *> init_vertex_zahvat(void);
    QVector<QVector4D *> init_vertex_kurs(void);
    QVector<QVector4D *> init_vertex_sector_indikator(void);
    QVector<QVector4D *> init_vertex_sector_indikator_color(void);


    void SetTarget(int D, float angl, int sizeX,int sizeD);

    float MetersTofloat(float Dln){
        if(Dln<0.0) Dln *=-1;
        return Dln/30000.0;
    }

    QString      framesPerSecond;

    QOpenGLDebugMessage  *message;
    QOpenGLDebugLogger   *m_logger;
    GLfloat               daln;

    float KU;
    float vizir_angle;
    float zahvat_angle;
    float Dalnost;

    int                   current_line;
    unsigned char         data[1024][1024];
    int                   poisk_regim;
    QTime m_time;
    int m_frames;
    int scale;

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE ;

     void messageLogged(const QOpenGLDebugMessage &msg);

signals:
    void needUpadateData();
    void FrameReady(void);
public slots:





};

#endif // SCANNING_CLASS_H
