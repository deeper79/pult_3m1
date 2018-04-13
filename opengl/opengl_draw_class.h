#ifndef OPENGL_DRAW_CLASS_H
#define OPENGL_DRAW_CLASS_H

#include <QWidget>
#include <QVector>
#include <QVector2D>
#include <QOpenGLContext>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>

typedef union{
    int data[11];
    struct{
        int vertex;
        int TextureCoord;
        int texture;
        int TrsX;
        int TrsY;
        int TrsZ;
        int scale_X;
        int scale_Y;
        int scale_Z;
        int angle_X;
        int angle_Y;
        int angle_Z;
        int regim;
        int haveTexture;
        int color;
        int dalnost;
    };
}ptr_U;

class opengl_draw_class
{

public:

    opengl_draw_class(void);
    bool init();
    void SetNameVertexShader   (QString str){name_vertex_shader = str;}
    void SetNameFragmentShader (QString str){name_fragment_shader = str;}
    void SetTextureImage(QImage  img){texture_image = img;}
    void Draw(void);
    void SetCustomVertex(QVector<QVector4D*> vector){
        vector_texture.clear();
        vector_vertex.clear();
        vector_vertex = vector;
    }
    void SetCustomColorVertex(QVector<QVector4D*> color){
        vector_color = color;
    }
    void SetNewTexture(QImage img);
    void SetTextureData(char *data);
    void SetTextureFormat(QOpenGLTexture::TextureFormat format);
    void InitTexture(int x,int y,QOpenGLTexture::TextureFormat format);

    void SetColor(QVector4D vec){
        color->setX(vec.x());
        color->setY(vec.y());
        color->setZ(vec.z());
        color->setW(vec.w());
    }

    void SetPoiskRegim(int rgm){regim = rgm;}

    inline void SetAngleX(double ang){angle_X = ang;}
    inline void SetAngleY(double ang){angle_Y = ang;}
    inline void SetAngleZ(double ang){angle_Z = ang;}

    inline void SetScaleX(double scale){scale_X = scale;}
    inline void SetScaleY(double scale){scale_Y = scale;}
    inline void SetScaleZ(double scale){scale_Z = scale;}

    inline void SetTranslateX(double trs){translate_X = trs;}
    inline void SetTranslateY(double trs){translate_Y = trs;}
    inline void SetTranslateZ(double trs){translate_Z = trs;}
    inline void SetDalnost(double daln)  {
        if(daln < 0.0) return;
        dalnost = (daln/30000.0-0.5)*0.934306569;
     }


    void SetGeometry(int x,int y,int width,int height);

    void setSizeGlView(int width,int height){
        gl_view_height = height;
        gl_view_width  = width;
    }
    inline bool inited(void) const {return init_done;}
    inline bool textute_inited(void) const {return haveTexture;}


private:
    double dalnost;
    ptr_U ptr;
    QVector<QVector4D *>   vector_vertex;
    QVector<QVector2D *>   vector_texture;
    QString                name_vertex_shader;
    QString                name_fragment_shader;
    QOpenGLShader         *vertex_shader;
    QOpenGLShader         *fragment_shader;
    QOpenGLShaderProgram  *programm;
    QImage                 texture_image;
    QOpenGLBuffer          vbo_buffer;
    QOpenGLTexture        *texture;
    QVector4D             *color;
    QVector<QVector4D *>   vector_color;
    bool init_done;
    bool haveTexture;

    double translate_X;
    double translate_Y;
    double translate_Z;
    double scale_X;
    double scale_Y;
    double scale_Z;
    double angle_X;
    double angle_Y;
    double angle_Z;
    int    regim;

    int gl_view_height;
    int gl_view_width;
    QOpenGLTexture::TextureFormat TFormat;

};

#endif // TEST_OPENGL_H
