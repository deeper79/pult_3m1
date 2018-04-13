#include "opengl_draw_class.h"

opengl_draw_class::opengl_draw_class(void):translate_X(0.0),translate_Y(0.0),translate_Z(0.0),
    scale_X(1.0),scale_Y(1.0),scale_Z(1.0),
    angle_X(0.0),angle_Y(0.0),
    gl_view_height(0),gl_view_width(0)

{
    memset(ptr.data,0x00,sizeof(ptr.data));

    init_done     = false;                          // флаг окончания иницилизации
    haveTexture   = false;                          // флаг наличия техтуры
    TFormat       = QOpenGLTexture::RGBA32U;        // Формат текстуры
    color         = new QVector4D(0.0,0.0,0.0,1.0); // цвет объекта без текстуры
    dalnost       = 0.5;
    angle_Z       = 0.0;
    regim         = 0;



    vector_vertex << new QVector4D( -1.0, -1.0  , 0.0f ,0.0f);
    vector_vertex << new QVector4D(  1.0, -1.0  , 0.0f ,0.0f);
    vector_vertex << new QVector4D( -1.0,  1.0  , 0.0f ,0.0f);


    vector_vertex << new QVector4D( -1.0,  1.0, 0.0f, 0.0f);
    vector_vertex << new QVector4D(  1.0, -1.0, 0.0f, 0.0f);
    vector_vertex << new QVector4D(  1.0,  1.0, 0.0f, 0.0f);


    vector_texture << new QVector2D( 0.0 , 0.0);
    vector_texture << new QVector2D( 1.0 , 0.0);
    vector_texture << new QVector2D( 0.0 , 1.0);

    vector_texture << new QVector2D( 0.0 , 1.0);
    vector_texture << new QVector2D( 1.0 , 0.0);
    vector_texture << new QVector2D( 1.0 , 1.0);
}

void opengl_draw_class::SetGeometry(int x, int y, int width, int height){

    if(gl_view_width <= 0 || gl_view_height <= 0 ) qDebug()<< "SetGeometry Error: size gl_view not set!";

    scale_X     =     (double)width/(double)gl_view_width;
    scale_Y     =     (double)height/(double)gl_view_height;

    translate_X =  2*((double)x/(double)gl_view_width)  - 1.0 + scale_X;
    translate_Y =-(2*((double)y/(double)gl_view_height) - 1.0 + scale_Y);

}
void opengl_draw_class::SetTextureFormat(QOpenGLTexture::TextureFormat format){
    TFormat = format;
}

void opengl_draw_class::SetTextureData(char *data){
    texture ->setData(QOpenGLTexture::Red,QOpenGLTexture::UInt8,data);
}
void opengl_draw_class::InitTexture(int x,int y,QOpenGLTexture::TextureFormat format){

    texture = new QOpenGLTexture(QOpenGLTexture::Target2D);
    texture->setMagnificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setMinificationFilter (QOpenGLTexture::LinearMipMapLinear);
    texture->setFormat(format);
    texture->setSize(x,y);
    texture->allocateStorage();
    haveTexture = true;
}

bool opengl_draw_class::init(){
    bool ok;

    if(gl_view_height == 0 || gl_view_width == 0){
        qDebug() << "Error: gl_view size not set!";
        return false;
    }
    if(!texture_image.isNull()){
        texture = new QOpenGLTexture(QOpenGLTexture::Target2D);
        texture->setMagnificationFilter(QOpenGLTexture::LinearMipMapLinear);
        texture->setMinificationFilter (QOpenGLTexture::LinearMipMapLinear);
        texture->setFormat(TFormat);
        texture->setSize(texture_image.width(),texture_image.height());
        texture->setData(texture_image);
        texture->allocateStorage();
        haveTexture = true;
    }

    vertex_shader = new QOpenGLShader(QOpenGLShader::Vertex);

    if(name_vertex_shader!=NULL) ok = vertex_shader->compileSourceFile(name_vertex_shader);
    else ok = vertex_shader->compileSourceFile(":/shaders/default_vertex_shader.vsh");

    if(!ok) qDebug()<<vertex_shader->log();

    fragment_shader = new QOpenGLShader(QOpenGLShader::Fragment);

    if(name_fragment_shader!=NULL) fragment_shader->compileSourceFile(name_fragment_shader);
    else fragment_shader->compileSourceFile(":/shaders/default_fragment_shader.fsh");

    if(!ok) qDebug()<<fragment_shader->log();

    programm = new QOpenGLShaderProgram;
    programm->addShader(vertex_shader);
    programm->addShader(fragment_shader);
    ok = programm->link();
    if(!ok) qDebug()<<programm->log();

    vbo_buffer.create();
    vbo_buffer.bind();


    QVector<GLfloat> buf;

    buf.resize(vector_vertex.count()  *4 +
               vector_texture.count() *2 +
               vector_vertex.count()  *4 +
               vector_vertex.count()  *1); //

    GLfloat *p = buf.data();

    for(int i=0;i<vector_vertex.count();i++){
        *p++ = vector_vertex[i]->x();
        *p++ = vector_vertex[i]->y();
        *p++ = vector_vertex[i]->z();
        *p++ = vector_vertex[i]->w();
    }

    for(int i=0;i<vector_texture.count();i++){
        *p++ = vector_texture[i]->x();
        *p++ = vector_texture[i]->y();
    }

    if(vector_color.isEmpty()){
        for(int i = 0;i<vector_vertex.count();i++){
            *p++ = color->x();
            *p++ = color->y();
            *p++ = color->z();
            *p++ = color->w();
        }
    }
    else
    {
        for(int i = 0;i<vector_color.count();i++){
            *p++ = vector_color[i]->x();
            *p++ = vector_color[i]->y();
            *p++ = vector_color[i]->z();
            *p++ = vector_color[i]->w();
        }
    }


    for(int i = 0;i<vector_vertex.count();i++) {
        if(haveTexture) *p++ = -1.0;
        else *p++ = 1.0;
    }



    // vbo_buffer.setUsagePattern(QOpenGLBuffer::DynamicDraw);

    vbo_buffer.allocate(buf.constData(),buf.size()*sizeof(GLfloat));
    vbo_buffer.release();

    ptr.vertex         = programm->attributeLocation  ("vertex");
    ptr.haveTexture    = programm->attributeLocation  ("haveTexture");
    ptr.dalnost        = programm->uniformLocation    ("dalnost");
    ptr.color          = programm->attributeLocation  ("color");
    ptr.TextureCoord   = programm->attributeLocation  ("texture_coordinate");
    ptr.texture        = programm->uniformLocation    ("texture");
    ptr.TrsX           = programm->uniformLocation    ("translate_X");
    ptr.TrsY           = programm->uniformLocation    ("translate_Y");
    ptr.TrsZ           = programm->uniformLocation    ("translate_Z");
    ptr.scale_X        = programm->uniformLocation    ("scale_X");
    ptr.scale_Y        = programm->uniformLocation    ("scale_Y");
    ptr.scale_Z        = programm->uniformLocation    ("scale_Z");
    ptr.angle_Z        = programm->uniformLocation    ("angle_Z");
    ptr.regim          = programm->uniformLocation    ("regim");

    init_done =true;

    return true;
}

void opengl_draw_class::Draw(void){

    programm ->bind();
    if(haveTexture) texture  ->bind();


    if(ptr.TrsX    != -1) programm->setUniformValue(ptr.TrsX     , (GLfloat)translate_X);
    if(ptr.TrsY    != -1) programm->setUniformValue(ptr.TrsY     , (GLfloat)translate_Y);
    if(ptr.TrsZ    != -1) programm->setUniformValue(ptr.TrsZ     , (GLfloat)translate_Z);
    if(ptr.scale_X != -1) programm->setUniformValue(ptr.scale_X  , (GLfloat)scale_X);
    if(ptr.scale_Y != -1) programm->setUniformValue(ptr.scale_Y  , (GLfloat)scale_Y);
    if(ptr.scale_Z != -1) programm->setUniformValue(ptr.scale_Z  , (GLfloat)scale_Z);
    if(ptr.angle_X != -1) programm->setUniformValue(ptr.angle_X  , (GLfloat)angle_X);
    if(ptr.angle_Y != -1) programm->setUniformValue(ptr.angle_Y  , (GLfloat)angle_Y);
    if(ptr.angle_Z != -1) programm->setUniformValue(ptr.angle_Z  , (GLfloat)angle_Z);
    programm->setUniformValue(ptr.regim    , (GLint)regim);
    if(ptr.dalnost != -1) programm->setUniformValue(ptr.dalnost  , (GLfloat)dalnost);


    programm->enableAttributeArray(ptr.vertex);

    if(haveTexture) programm->enableAttributeArray(ptr.TextureCoord);
    programm->enableAttributeArray(ptr.color);
    programm->enableAttributeArray(ptr.haveTexture);


    vbo_buffer.bind();


    if(haveTexture) {
        programm->setAttributeBuffer(ptr.vertex,GL_FLOAT, 0, 4);

        programm->setAttributeBuffer(ptr.TextureCoord,GL_FLOAT,
                                     vector_vertex.count()  *sizeof(GLfloat)*4, 2);

        programm->setAttributeBuffer(ptr.color,GL_FLOAT,
                                     vector_vertex.count()  *sizeof(GLfloat)*4 +
                                     vector_texture.count() *sizeof(GLfloat)*2, 4);

        programm->setAttributeBuffer(ptr.haveTexture,GL_FLOAT,
                                     vector_vertex.count()  *sizeof(GLfloat)*4 +
                                     vector_texture.count() *sizeof(GLfloat)*2 +
                                     vector_vertex.count() *sizeof(GLfloat)*4, 1);

    }
    else
    {
        programm->setAttributeBuffer(ptr.vertex,GL_FLOAT, 0, 4);

        programm->setAttributeBuffer(ptr.color,GL_FLOAT,
                                     vector_vertex.count()  *sizeof(GLfloat)*4, 4);

        programm->setAttributeBuffer(ptr.haveTexture,GL_FLOAT,
                                     vector_vertex.count()  *sizeof(GLfloat)*4 +
                                     vector_vertex.count()  *sizeof(GLfloat)*4,1);

    }

    vbo_buffer.release();

    glDrawArrays(GL_TRIANGLES,0,vector_vertex.size());

    if(haveTexture) programm->disableAttributeArray(ptr.TextureCoord);

    programm->disableAttributeArray(ptr.vertex);
    programm->disableAttributeArray(ptr.color);
    programm->disableAttributeArray(ptr.haveTexture);


    if(haveTexture) texture->release();

    programm->release();

}

void opengl_draw_class::SetNewTexture(QImage img){

    texture->destroy();
    texture->setMagnificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setMinificationFilter (QOpenGLTexture::LinearMipMapLinear);
    texture->setFormat(QOpenGLTexture::RGBA32U);
    texture->setSize(img.width(),img.height());
    texture->setData(img);
    texture->allocateStorage();
}


