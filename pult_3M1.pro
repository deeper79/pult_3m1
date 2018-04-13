#-------------------------------------------------
#
# Project created by QtCreator 2016-08-22T13:33:48
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT += multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pult_3M1
TEMPLATE = app


SOURCES += main.cpp\
    pult_3m1_main_class.cpp \
    panels/panel_vizir_class.cpp \
    scannig/scanning_class.cpp \
    scannig/um_scannig_class.cpp \
    panels/panel_antena_class.cpp \
    panels/panel_param_class.cpp \
    panels/panel_error_class.cpp \
    widgets/autotrack_dlanost_class.cpp \
    panels/panel_RLS_class.cpp \
    widgets/miliampermeter_class.cpp \
    video/video.cpp \
    video/videowidget.cpp \
    usb/linux_usb_class.cpp \
    widgets/tou_keyboard_class.cpp \
    video/grab_screen_class.cpp \
    widgets/playback_class.cpp \
    opengl/opengl_draw_class.cpp \
    opengl/draw_texture_class.cpp \
    usb/usb_adc_rls_class.cpp \
    usb/usb_adc_rlso_class.cpp \
    usb/usb_mko_pribor1m_class.cpp \
    usb/usb_mko_bc123_class.cpp \
    opengl/pult.cpp




HEADERS  += \
    pult_3m1_main_class.h \
    panels/panel_vizir_class.h \
    scannig/scanning_class.h \
    scannig/um_scannig_class.h \
    panels/panel_antena_class.h \
    panels/panel_param_class.h \
    panels/panel_error_class.h \
    widgets/autotrack_dalnost_class.h \
    panels/panel_RLS_class.h \
    widgets/miliampermeter_class.h \
    video/video.h \
    video/videowidget.h \
    usb/linux_usb_class.h \
    widgets/tou_keyboard_class.h \
    video/grab_screen_class.h \
    widgets/playback_class.h \
    opengl/opengl_draw_class.h \
    opengl/draw_texture_class.h \
    opengl/pult.h \
    usb/usb_adc_rls_class.h \
    usb/usb_adc_rlso_class.h \
    usb/usb_mko_pribor1m_class.h \
    usb/usb_mko_bc123_class.h




DISTFILES += \
    fshrader_kurs.frag \
    vsharder_kurs.vert \
    fshader_scan.frag \
    fshader_vizir.frag \
    fshader_zahvat.frag \
    vshader_scan.vert \
    vshader_vizir.vert \
    vshader_zahvat.vert \
    fsharder_vizir_um.frag \
    vsharder_vizir_um.vert \
    vshader_scan_sektor.vert \
    fshader_scan_sektor.frag


RESOURCES += \
    resurces.qrc


#QMAKE_CXXFLAGS_DEBUG += -O

INCLUDEPATH += /opt/intel/ipp/include

QMAKE_CXXFLAGS +=  -fopenmp
QMAKE_LFLAGS   +=  -fopenmp

LIBS += -L/opt/intel/ipp/lib/intel64 -lippcore  -lippi -lippvm -lipps -lavcodec -lavformat -lavutil -lswscale -lX11 -lXext -lippcc
#QMAKE_CXXFLAGS_DEBUG += -O3

target.path = /home/pult
INSTALLS += target

