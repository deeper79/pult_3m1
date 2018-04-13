#include "scanning_class.h"
extern "C" {
#include <X11/Xlib.h>
#include <X11/Xutil.h>
}
Display *display ;
Window rootWindow;

scanning_class::scanning_class(QWidget *parent,int posX,int posY):QOpenGLWidget(parent),
    current_line(100),poisk_regim(pult::Krug),scale(0)
{
    
    setGeometry(posX,posY,1096,1096);
    
    sektor_indikator      = new opengl_draw_class;
    vizir                 = new opengl_draw_class;
    scan_back             = new opengl_draw_class;
    scan                  = new opengl_draw_class;
    kurs                  = new opengl_draw_class;
    zahvat                = new opengl_draw_class;
    sector_indicator_line = new opengl_draw_class;
    //usb_adc_rls           = new usb_adc_rls_class;

    sector_indicator_line->setSizeGlView(1096,1096);
    sector_indicator_line->SetCustomVertex(init_vertex_sector_indikator());
    sector_indicator_line->SetColor(QVector4D(0.4,0.2,0.0,1.0));
    sector_indicator_line->SetGeometry(617,39,200,200);
    sector_indicator_line->SetCustomColorVertex(init_vertex_sector_indikator_color());
    
    
    sektor_indikator->SetTextureImage(draw_texture_class::TextureSectorIndikator());
    sektor_indikator->setSizeGlView(1024,1024);
    sektor_indikator->SetGeometry(550,10,240,240);
    sektor_indikator->SetTranslateZ(-0.1);
    
    
    vizir->SetCustomVertex(init_vertex_vizir());
    vizir->SetColor(QVector4D(0.0,1.0,0.0,0.5));
    vizir->setSizeGlView(1096,1096);
    vizir->SetGeometry(0,0,1096,1096);
    
    
    scan_back->setSizeGlView(1096,1096);
    scan_back->SetGeometry(0,0,1096,1096);
    scan_back->SetTextureImage(draw_texture_class::TextureKrug(pult::Krug));
    scan_back->SetNameFragmentShader(":/shaders/fshader_scan_back.fsh");
    scan_back->SetNameVertexShader(":/shaders/vshader_scan_back.vsh");
    
    
    scan->setSizeGlView(1096,1096);
    scan->SetGeometry(36,36,1024,1024);
    scan->SetNameFragmentShader(":/shaders/fshader_scan.frag");
    scan->SetNameVertexShader  (":/shaders/vshader_scan.vert");
    scan->SetTranslateZ(0.01);
    
    kurs->SetColor(QVector4D(0.0,0.0,1.0,1.0));
    kurs->SetCustomVertex(init_vertex_kurs());
    kurs->setSizeGlView(1096,1096);
    kurs->SetGeometry(0,0,1096,1096);
    
    zahvat->SetColor(QVector4D(1.0,1.0,0.0,1.0));
    zahvat->SetCustomVertex(init_vertex_zahvat());
    zahvat->setSizeGlView(1096,1096);
    zahvat->SetGeometry(0,0,1096,1096);
    
    //connect(this,SIGNAL(FrameReady()),this,SLOT(ImageRead()));

   // display = XOpenDisplay(NULL);
  //  rootWindow = RootWindow(display, DefaultScreen(display));

    QSurfaceFormat*  surf_format = new QSurfaceFormat();
    surf_format->setSamples(4);
    setFormat(*surf_format);
    SetTarget(27000,1,10,600);
}



scanning_class::scanning_class(QWidget *parent,int posX,int posY,int width,int height):QOpenGLWidget(parent),
    poisk_regim(pult::Krug),scale(0)
{
    setGeometry(posX,posY,width,height);
    connect(this,           SIGNAL(ScaleCahged(int)), this,   SLOT(ScaleCahngedSlot(int)));
}

void scanning_class::initializeGL()
{
    
    initializeOpenGLFunctions();
    
    sektor_indikator ->init();
    scan_back        ->init();
    scan             ->init();
    kurs             ->init();
    vizir            ->init();
    zahvat           ->init();
    sector_indicator_line->init();
    scan             ->InitTexture(1024,1024,QOpenGLTexture::R8_UNorm);
    
    glClearColor(0.0, 0.5, 0.0, 1.0);
    
}

void scanning_class::resizeGL(int nWidth, int nHeight)
{
    
    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
    
}

void scanning_class::paintGL() // рисование
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    //  glEnable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);
    
    QPainter painter;
    static int step =0;
    
     if(step  == 1) {
        for(int i=0;i<1024;i++){
            for(int j=0;j<512;j++)
                if(data[j][i]>0x04) {
                    data[j][i] =data[j][i]-0x04;
                }
        }
        step = 0;
    }
    step++;
  //
    scan      ->Draw();
    scan_back ->Draw();

    zahvat    ->Draw();
    scan      ->SetTextureData((char *)data);
    vizir->Draw();



    switch (poisk_regim) {
    case pult::Krug:
        kurs      ->Draw();
        kurs      ->SetAngleZ(45);
        zahvat    ->SetAngleZ(zahvat_angle);
        zahvat    ->SetDalnost(Dalnost);
        vizir     ->SetAngleZ(-vizir_angle);

        break;
    case pult::Sektor:
        sektor_indikator ->Draw();
        scan_back        ->SetAngleZ(-zahvat_angle);
        scan             ->SetAngleZ(zahvat_angle);
        zahvat           ->SetDalnost(Dalnost);
        vizir            ->SetAngleZ(-vizir_angle);
         sector_indicator_line->Draw();
         sector_indicator_line->SetAngleZ(zahvat_angle);

        break;
    case pult::Regim_1A:
        
        kurs  ->Draw();
        kurs  ->SetTranslateX(0.5);
        vizir ->SetTranslateX(vizir_angle/360.0*1.6008316);

        zahvat ->SetDalnost(Dalnost);
        zahvat ->SetTranslateX(zahvat_angle/360.0*1.6008316);

        break;
    default:
        break;
    }

    glDisable(GL_MULTISAMPLE);
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);

    QFont font;
    font.setPixelSize(24);
    painter.begin(this);
    
    painter.setFont(font);
    
    if (const int elapsed = m_time.elapsed()) {
        
        framesPerSecond.setNum(m_frames /(elapsed / 1000.0), 'f', 2);
        painter.setPen(Qt::white);
        painter.drawText(400, 140, framesPerSecond + " paintGL calls / s");
    }

    painter.end();

  //  XImage* img;
    //QTime time;

  //   time.start();

   //  img = XGetImage(display, rootWindow, 0, 0,1600, 1200, AllPlanes, ZPixmap);

  //   qDebug() << time.elapsed();
    
    if (!(m_frames % 100)) {
        m_time.start();
        m_frames = 0;
    }
    ++m_frames;

    emit needUpadateData();
    update();
    // emit FrameReady();
}



void scanning_class::SetTarget(int D, float angl, int sizeX, int sizeD){
    
    float tempD_b = (512/30000.0)*D;
    float tempD_e = tempD_b+(512/30000.0)*sizeD;
    float tempA_b = (1024.0/360.0)*angl;
    float tempA_e = tempA_b + (1024.0/360.0)*sizeX;
    
    for(int i=tempD_b;i<tempD_e;i++){
        for(int j=tempA_b;j<tempA_e;j++){
            data[i][j] = 0xFF;
        }
    }
    
}

void scanning_class::setPoiskRegim(int ena){
    
    poisk_regim = ena;
    
    switch (poisk_regim) {
    case pult::Krug:
        scan_back->SetNewTexture(draw_texture_class::TextureKrug(pult::Krug));

        zahvat->SetTranslateY(0.0);
        zahvat->SetScaleY(1.0);
        zahvat->SetScaleX(1.0);
        zahvat->SetTranslateX(0.0);

        kurs->SetTranslateX(0.0);
        kurs->SetScaleY(1.0);

        vizir->SetTranslateY(0.0);
        vizir->SetScaleY(1.0);
        vizir->SetScaleX(1.0);
        vizir->SetTranslateX(0.0);
        break;

    case pult::Sektor:

        scan_back->SetNewTexture(draw_texture_class::TextureKrug(pult::Sektor));

        zahvat->SetTranslateY(-1.0);
        zahvat->SetScaleY(1.4);
        zahvat->SetScaleX(1.4);
        zahvat->SetAngleZ(0.0);
        zahvat->SetTranslateX(0.0);

        vizir->SetTranslateY(-1.0);
        vizir->SetTranslateX(0.0);
        vizir->SetScaleY(1.4);
        vizir->SetScaleX(1.4);

        break;
    case pult::Regim_1A:
        scan_back->SetAngleZ(0.0);
        scan->SetAngleZ(0.0);
        scan_back->SetNewTexture(draw_texture_class::DrawScreenRLS_IndicatorA(scale));
        kurs->SetScaleY(0.711757813);
        kurs->SetAngleZ(0.0);

        vizir->SetAngleZ(0.0);
        vizir->SetScaleY(1.42);
        vizir->SetTranslateY(-0.66);

        zahvat->SetAngleZ(0.0);
        zahvat->SetScaleY(1.42);
        zahvat->SetTranslateY(-0.66);
        break;
    default:
        break;
    }
    
    scan     -> SetPoiskRegim(poisk_regim);// Переключения программы шейдера
    scan_back-> SetPoiskRegim(poisk_regim);
    
    return;
    
}

void scanning_class::SetScaleScan(int scl){
    scan_back->SetNewTexture(draw_texture_class::DrawScreenRLS_IndicatorA(scl));
}


scanning_class::~scanning_class(){
    
}

QVector<QVector4D *> scanning_class::init_vertex_sector_indikator(){
    QVector<QVector4D*> vertex;
    float z  =-0.2f;
    vertex << new QVector4D( -0.015f,  1.0, z,0.0f);
    vertex << new QVector4D( -0.015f,  0.0, z,0.0f);
    vertex << new QVector4D(  0.015f,  0.0, z,0.0f);

    vertex << new QVector4D( -0.015f,  1.0, z,0.0f);
    vertex << new QVector4D(  0.015f,  0.0, z,0.0f);
    vertex << new QVector4D(  0.015f,  1.0, z,0.0f);


    vertex << new QVector4D( vertex[0]->x()*qCos(qDegreesToRadians(30.0))-vertex[0]->y()*qSin(qDegreesToRadians(30.0)),
            vertex[0]->y()*qCos(qDegreesToRadians(30.0))+vertex[0]->x()*qSin(qDegreesToRadians(30.0)), z,0.0f);

    vertex << new QVector4D( vertex[1]->x()*qCos(qDegreesToRadians(30.0))-vertex[1]->y()*qSin(qDegreesToRadians(30.0)),
            vertex[1]->y()*qCos(qDegreesToRadians(30.0))+vertex[1]->x()*qSin(qDegreesToRadians(30.0)), z,0.0f);

    vertex << new QVector4D( vertex[2]->x()*qCos(qDegreesToRadians(30.0))-vertex[2]->y()*qSin(qDegreesToRadians(30.0)),
            vertex[2]->y()*qCos(qDegreesToRadians(30.0))+vertex[2]->x()*qSin(qDegreesToRadians(30.0)), z,0.0f);



    vertex << new QVector4D( vertex[3]->x()*qCos(qDegreesToRadians(30.0))-vertex[3]->y()*qSin(qDegreesToRadians(30.0)),
            vertex[3]->y()*qCos(qDegreesToRadians(30.0))+vertex[3]->x()*qSin(qDegreesToRadians(30.0)), z,0.0f);

    vertex << new QVector4D( vertex[4]->x()*qCos(qDegreesToRadians(30.0))-vertex[4]->y()*qSin(qDegreesToRadians(30.0)),
            vertex[4]->y()*qCos(qDegreesToRadians(30.0))+vertex[4]->x()*qSin(qDegreesToRadians(30.0)), z,0.0f);

    vertex << new QVector4D( vertex[5]->x()*qCos(qDegreesToRadians(30.0))-vertex[5]->y()*qSin(qDegreesToRadians(30.0)),
            vertex[5]->y()*qCos(qDegreesToRadians(30.0))+vertex[5]->x()*qSin(qDegreesToRadians(30.0)), z,0.0f);



    vertex << new QVector4D( vertex[0]->x()*qCos(qDegreesToRadians(-30.0))-vertex[0]->y()*qSin(qDegreesToRadians(-30.0)),
            vertex[0]->y()*qCos(qDegreesToRadians(-30.0))+vertex[0]->x()*qSin(qDegreesToRadians(-30.0)), z,0.0f);

    vertex << new QVector4D( vertex[1]->x()*qCos(qDegreesToRadians(-30.0))-vertex[1]->y()*qSin(qDegreesToRadians(-30.0)),
            vertex[1]->y()*qCos(qDegreesToRadians(-30.0))+vertex[1]->x()*qSin(qDegreesToRadians(-30.0)), z,0.0f);

    vertex << new QVector4D( vertex[2]->x()*qCos(qDegreesToRadians(-30.0))-vertex[2]->y()*qSin(qDegreesToRadians(-30.0)),
            vertex[2]->y()*qCos(qDegreesToRadians(-30.0))+vertex[2]->x()*qSin(qDegreesToRadians(-30.0)), z,0.0f);


    vertex << new QVector4D( vertex[3]->x()*qCos(qDegreesToRadians(-30.0))-vertex[3]->y()*qSin(qDegreesToRadians(-30.0)),
            vertex[3]->y()*qCos(qDegreesToRadians(-30.0))+vertex[3]->x()*qSin(qDegreesToRadians(-30.0)), z,0.0f);

    vertex << new QVector4D( vertex[4]->x()*qCos(qDegreesToRadians(-30.0))-vertex[4]->y()*qSin(qDegreesToRadians(-30.0)),
            vertex[4]->y()*qCos(qDegreesToRadians(-30.0))+vertex[4]->x()*qSin(qDegreesToRadians(-30.0)), z,0.0f);

    vertex << new QVector4D( vertex[5]->x()*qCos(qDegreesToRadians(-30.0))-vertex[5]->y()*qSin(qDegreesToRadians(-30.0)),
            vertex[5]->y()*qCos(qDegreesToRadians(-30.0))+vertex[5]->x()*qSin(qDegreesToRadians(-30.0)), z,0.0f);

    return vertex;

}

QVector<QVector4D *> scanning_class::init_vertex_sector_indikator_color(void){
    QVector<QVector4D*> color;

    color << new QVector4D(1.0,1.0,0.0,1.0);
    color << new QVector4D(1.0,1.0,0.0,1.0);
    color << new QVector4D(1.0,1.0,0.0,1.0);

    color << new QVector4D(1.0,1.0,0.0,1.0);
    color << new QVector4D(1.0,1.0,0.0,1.0);
    color << new QVector4D(1.0,1.0,0.0,1.0);

    color << new QVector4D(0.0,0.5,0.0,1.0);
    color << new QVector4D(0.0,0.5,0.0,1.0);
    color << new QVector4D(0.0,0.5,0.0,1.0);

    color << new QVector4D(0.0,0.5,0.0,1.0);
    color << new QVector4D(0.0,0.5,0.0,1.0);
    color << new QVector4D(0.0,1.0,0.0,1.0);

    color << new QVector4D(0.0,0.5,0.0,1.0);
    color << new QVector4D(0.0,0.5,0.0,1.0);
    color << new QVector4D(0.0,0.5,0.0,1.0);

    color << new QVector4D(0.0,0.5,0.0,1.0);
    color << new QVector4D(0.0,0.5,0.0,1.0);
    color << new QVector4D(0.0,0.5,0.0,1.0);

    return color;
}

QVector<QVector4D*> scanning_class::init_vertex_kurs(void){

    float z  =-0.2f;

    QVector<QVector4D*> vertex;

    float witdh_zav = -0.003f;
    vertex << new QVector4D(-witdh_zav, PointToTexel( 72+60) ,z ,0.0f);
    vertex << new QVector4D( witdh_zav, PointToTexel( 72+60) ,z,0.0f);
    vertex << new QVector4D(-witdh_zav, PointToTexel(-72)    ,z,0.0f);

    vertex << new QVector4D(-witdh_zav, PointToTexel(-72)    ,z,0.0f);
    vertex << new QVector4D(+witdh_zav, PointToTexel( 72+60) ,z,0.0f);
    vertex << new QVector4D(+witdh_zav, PointToTexel(-72)    ,z,0.0f);

    vertex << new QVector4D(-0.01f, PointToTexel( 72+60) ,z,0.0f);
    vertex << new QVector4D( 0.01f, PointToTexel( 72+60) ,z,0.0f);
    vertex << new QVector4D( 0.0  , PointToTexel( 72)    ,z,0.0f);

    return vertex;

}
QVector<QVector4D*>  scanning_class::init_vertex_vizir(void){

    float z = -0.002f;
    QVector<QVector4D*> vertex;

    vertex << new QVector4D( -0.005f,  PointToTexel(72), z,0.0f);
    vertex << new QVector4D( -0.005f,  0.0, z,0.0f);
    vertex << new QVector4D(  0.005f,  0.0, z,0.0f);

    vertex << new QVector4D( -0.005f,  PointToTexel(72), z,0.0f);
    vertex << new QVector4D(  0.005f,  0.0, z,0.0f);
    vertex << new QVector4D(  0.005f,  PointToTexel(72), z,0.0f);
    return vertex;
}

QVector<QVector4D*> scanning_class::init_vertex_zahvat(void){
    float witdh_zav_h = 0.003f;
    float witdh_zav_v = 0.004f;
    float leght_strob = 0.020f;
    float D = 0.5f;
    float strob = MetersTofloat(1000.0);
    float z = -0.003f;

    QVector<QVector4D*> vertex;

    vertex << new QVector4D( -witdh_zav_h,    D           ,z, 2.0f);
    vertex << new QVector4D( -witdh_zav_h,    0.0f        ,z, 0.0f);
    vertex << new QVector4D(  witdh_zav_h,    0.0         ,z, 0.0f);

    vertex << new QVector4D( -witdh_zav_h,    D           ,z, 2.0f);
    vertex << new QVector4D(  witdh_zav_h,    0.0f        ,z, 0.0f);
    vertex << new QVector4D(  witdh_zav_h,    D           ,z, 2.0f);

    vertex << new QVector4D(  leght_strob,  D             ,z, 2.0f);
    vertex << new QVector4D( -leght_strob,  D+witdh_zav_v ,z, 2.0f);
    vertex << new QVector4D( -leght_strob,  D             ,z, 2.0f);

    vertex << new QVector4D( -leght_strob,  D+witdh_zav_v ,z, 2.0f);
    vertex << new QVector4D(  leght_strob,  D             ,z, 2.0f);
    vertex << new QVector4D(  leght_strob,  D+witdh_zav_v ,z, 2.0f);

    vertex << new QVector4D(  leght_strob,  D+strob             ,z, 2.0f);
    vertex << new QVector4D( -leght_strob,  D+witdh_zav_v+strob ,z, 2.0f);
    vertex << new QVector4D( -leght_strob,  D+strob             ,z, 2.0f);

    vertex << new QVector4D( -leght_strob,  D+witdh_zav_v+strob ,z, 2.0f);
    vertex << new QVector4D(  leght_strob,  D+strob             ,z, 2.0f);
    vertex << new QVector4D(  leght_strob,  D+witdh_zav_v+strob ,z, 2.0f);

    vertex << new QVector4D( -witdh_zav_h,  PointToTexel(72)    ,z, 0.0f);
    vertex << new QVector4D( -witdh_zav_h,  D+strob             ,z, 2.0f);
    vertex << new QVector4D(  witdh_zav_h,  D+strob             ,z, 2.0f);

    vertex << new QVector4D( -witdh_zav_h,  PointToTexel(72)    ,z, 0.0f);
    vertex << new QVector4D(  witdh_zav_h,  D+strob             ,z, 2.0f);
    vertex << new QVector4D(  witdh_zav_h,  PointToTexel(72)    ,z, 0.0f);

    return vertex;
}
