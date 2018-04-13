#include "usb_mko_pribor1m_class.h"


usb_mko_Pribor1M_class::usb_mko_Pribor1M_class(QObject *parent) : QObject(parent)
{

    thread_usb       = new QThread();
    usb_mko_Pribor1M = new linux_usb_class();

    usb_mko_Pribor1M->setDeviceName("/dev/plata_mko_1");
    usb_mko_Pribor1M->addEndpoint(4,64,IN,0x81,0);
    usb_mko_Pribor1M->initUsbDevice();

    connect(usb_mko_Pribor1M, SIGNAL(haveData(char *,int)),this, SLOT(dataRecived(char *,int)));
    connect(thread_usb,       SIGNAL(started()),usb_mko_Pribor1M, SLOT(read_data()));
    dev_open = usb_mko_Pribor1M->open_dev();

    if(!dev_open){
        qDebug() << "Cant open device mko Pribor1M";
        return;
    }
    for(int i=32;i<64;i++){
        Data_out_Pribor1M.data[i] = i;
    }

    usb_mko_Pribor1M->moveToThread(thread_usb);

}

void usb_mko_Pribor1M_class::dataRecived(char *data,int i){

    memcpy(&Data_in_Pribor1M.data[0],data,64);
    usb_mko_Pribor1M->sendData(&Data_out_Pribor1M.data[0],64);
}
