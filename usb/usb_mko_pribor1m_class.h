#ifndef USB_MKO_PRIBOR1M_H
#define USB_MKO_PRIBOR1M_H

#include <QObject>
#include "../opengl/pult.h"
#include "linux_usb_class.h"
#include <QThread>

class usb_mko_Pribor1M_class : public QObject
{
    Q_OBJECT
public:
    explicit usb_mko_Pribor1M_class(QObject *parent = nullptr);
    bool start(void){
        if(!dev_open) return false;
        thread_usb->start();
        usb_mko_Pribor1M->start_read();
        return true;
    }
    const char* data(void){return (const char *)buffer_to_write_Pribor1M;}

private:

    linux_usb_class     *usb_mko_Pribor1M;
    Data_out_Pribor1M_S  Data_out_Pribor1M;
    Data_in_Pribor1M_S   Data_in_Pribor1M;
    QThread             *thread_usb;
    bool dev_open;

    char buffer_to_write_Pribor1M[4096];

signals:

public slots:

     void dataRecived(char *data,int i);
};

#endif // USB_MKO_PRIBOR1M_H
