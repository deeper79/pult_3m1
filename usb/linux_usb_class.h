#ifndef LINUX_USB_CLASS_H
#define LINUX_USB_CLASS_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <poll.h> /* poll */
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <QByteArray>
#include <QDebug>
#include <QObject>
#include <QTimer>

typedef struct{
    uint count;     // количество полученных посылок до получения сигнала данные готовы
    uint len;       // количество байт в одной опсылке
    bool type;      // тип точки (IN,OUT)
    uint offset;    // смещение в буффере класса
    uint offset_in; // смещенин в буффере устройства
    uint num;       // текущая принимаемая посылка
    uint adress;    // номер(адресс) точки
}endpoint_S;


#define USB_MAGIC (100) // Магическое число для управления устройством

#define DEV_CMD_SET_START   _IO(USB_MAGIC,0)	  // команда начала работы
#define DEV_CMD_SET_STOP    _IO(USB_MAGIC,1)	  // команда окончания работы
#define DEV_OFFSET_DATA     _IOR(USB_MAGIC,2,int) // передача значения текущей конечной точки

class linux_usb_class:public QObject
{
    Q_OBJECT // енто понятно
public:
    linux_usb_class(QObject *parent = 0);                                        // коструктор класса
    bool open_dev(void);                                                         // функция открытия устройства USB
    void close_dev(void);                                                        // функия закрытия устройства
    void start_read(void);                                                       // начало работы устройства (взод urb на прием(сторона хоста))
    void stop_read(void);                                                        // остановка работы устройства (kill_urb)
    void setDeviceName(QString name) {dev_name = name;}                          // установка названия устройсва в dev
    void addEndpoint(uint count, uint len, bool type, uint adress, uint offset); // заполнение листа эндпонитами
    bool initUsbDevice(void);                                                    // иницилизачия нужных буфферов, выделение память и т.д.
    void setTimeOut(int time){timeout = time;}                                   //  установка таймаута мс
    void sendData(char *data, int len);                                          // отправка данных устройству

    inline endpoint_S* getEndPoint(uint num) {                                   // передача другому классу значений структруы точки
      for(int i=0;i < endpoint.size();i++){
            if(endpoint[i].adress == num){
              return &endpoint[i];
            }
      }
      return NULL;
    }


private:
    QTimer *timer_timeout ;       // таймер тайаута
    QString dev_name;             // название устройства в dev
    QVector<endpoint_S> endpoint; // лист конечных точек устнройства (заполнять самому)
    int fd;                       // указатель на устройство
    struct pollfd pfd;            // структура пол для получения прерывания от устройства о получении данных
    bool started;                 // флаг работы устройства
    int timeout;                  // текущие время тайаута
    char *buffer_in;              // буффер принятых данных


signals:

    void haveData(char *data, int number_point); //  сигнал наличия данных
    void TimeOut(void);                          // сигнал тайаута

public slots:
    int read_data ();   // функция чтения данных (завязана на поток метод started())

private slots:
    void slotTimeOut(void); // слот тайаута

};

#endif // LINUX_USB_CLASS_H
