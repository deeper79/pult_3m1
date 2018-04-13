#ifndef VIDEO_H
#define VIDEO_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <linux/v4l2-common.h>
#include <linux/videodev2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <getopt.h>             /* getopt_long() */
#include <fcntl.h>              /* low-level i/o */
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <QCameraInfo>
#include <ippi.h>
#include <ippcore.h>
#include <ippcore_l.h>
#include <ippvm.h>
#include <ipps.h>
#include <omp.h>
#include <linux/videodev2.h>

#define MAX_NUM_THREADS 16 // количество паралельных потоков

struct buffer {
    void   *start;        // указатель на начало буффера
    size_t  length;       // длина буффера
};

class V4L2_video_class : public QObject
{
    Q_OBJECT

public:
    V4L2_video_class(QObject *parent = 0);// Коструктор класса
    ~V4L2_video_class();                  // Деструктор класса
    bool StartCapturing(void);            // Включение завхвата изображения
    bool StopCapturing(void);             // Отключение завхвата изображения
    QList<QString *> GetAviableDevice(void); // Список устройств захвата
    void SetVideoInput(int num);          // Установка номера видеовхода
    bool OpenDevice(const char *dev);     // Открытие устройства
    bool InitDevice(void);                // Иницилизация устройства
    void SuppotedFormatFrame(void);       // Не доработана
    void DeInitDevice(void);              // Деиницилизация устройства
    QString CurrentFormatInput() const;   // Текущий формат входа
    void SuppotedControls(void);
    void enumerate_menu(__u32 id);
    void allControl(void);

    void EnableResize(bool on){           // Включение изменения разрешения фрейма
        ResizeEnable = on;
    }
    void SetResize(int x, int y){         // Установка выходного разрешения фрейма

        delete out;                         // Удаление ткущего изображения
        rX = x;                             // Новое значение ширины кадра в пикселях
        rY = y;                             // Новое значение высоты кадра в пикселях
        out = new QImage(rX,rY,QImage::Format_RGB888); // Создание нового изображения
    }


private:
    struct v4l2_queryctrl queryctrl;
    struct v4l2_querymenu querymenu;
    int            rX;                               // ширина кадра в пикселях
    int            rY;                               // высота кадра в пикселях
    int            num_input;                        // текущий вход видеозахвата
    int            pDevice;                          // указатель на устройство
    uint           n_buffers;                        // буфферы nmap
    QImage        *img;                              // указатель на текущий кадр
    QImage        *out;                              // указатель на выходной кадр
    struct buffer *buffers;                          // указатель на структуру буфферов nmap (начало,длина)
    const char    *dev_name;                         // название устройства
    bool           ResizeEnable;                     // флаг включения перемаштобирования


    int  read_frame(void);                                  // чтение кадра
    void SuppotedFormatInput(void) const;                   // поддерживаемые форматы кадров
    bool SelectFormatInput(v4l2_std_id std_id,uint number); // установка формата входного сигнала
    bool SetFrameFormat(QSize size={720,576}) const;        // установка разрешения завата кадра
    bool ResizeFrame(void);                                 // маштабирование кадра (один поток)
    bool ResizeFrameOpenMP(void);                           // маштабирование кадра (много поточное)
    void process_image(const void *p);                      // формирование выходного изображения
    bool InitMmap(void);                                    // иницилизация буфферов nmap
   // bool ResetCroppingParameters(void);
   // bool VideoDownSampling(void);

signals:
    void  haveFrame(QImage *img);                             // сигнал наличия кадра
public slots:
    void    MainLoop(void);                                   // бесконечный цикл получения кадров
};

#endif // VIDEOWIDGET_H
