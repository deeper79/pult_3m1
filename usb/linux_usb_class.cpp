#include "linux_usb_class.h"

linux_usb_class::linux_usb_class(QObject *parent)
    :QObject(parent)
{
    started = false;                // флаг устройство запущено
    timeout = 3000;                 // начальное значение тайаута мс
    timer_timeout = new QTimer();   // создание таймера тайаута
    
    connect(timer_timeout,SIGNAL(timeout()),this,SLOT(slotTimeOut())); // связь сигнала и слота тайаута

}

void linux_usb_class::slotTimeOut(){
    emit TimeOut(); // установить сигнал таймаут (лучше так, потоки РАЗНЫЕ!!!)
}

void linux_usb_class::start_read(){
    
    if(started) return; // если уже работает выходим
    
    if(ioctl(fd,DEV_CMD_SET_START)<0) {//передача команды начала преобразования
        qDebug() <<"Error ioctl failed:" << strerror(errno); // передача команды устройству не прошла
        return;
    }
    
    qDebug() <<  "Device start";
    timer_timeout->start(timeout); // запускаем таймер таймаут
    started = true;                // устанавливаем флаг устройство запущено
}

bool linux_usb_class::initUsbDevice(void){

    uint len_in  = 0;
    uint len_out = 0;

    if(endpoint.size() == 0) {
        qDebug() << "Not endpoint set";
        return false;
    }

    for(int i=0;i<endpoint.size();i++){
        if(!endpoint[i].type){
            len_in  += endpoint[i].count*endpoint[i].len;
        }
        else{
            len_out += endpoint[i].count*endpoint[i].len;
        }
    }

    buffer_in  = (char *)malloc(len_in);


    memset(buffer_in, 0x00,len_in);


    return true;

}
void linux_usb_class::stop_read(){
    if(!started) return;
    if(ioctl(fd,DEV_CMD_SET_STOP)<0){
        qDebug() <<"Error ioctl failed" << errno << strerror(errno);
        return;
    }
    started = false;

    qDebug() <<  "Device stopped\n";

}

bool linux_usb_class::open_dev(){

    if(dev_name.isNull()){
        qDebug() << "Device name not set";
        return false;
    }
    fd = open(dev_name.toUtf8().constData(),O_RDWR);
    if(fd < 0){
        qDebug() << "Can`t open device: "<< strerror(errno);

        return false;
    }
    return true;
}
void linux_usb_class::close_dev(){
    close(fd);
}
void linux_usb_class::addEndpoint(uint count, uint len, bool type, uint adress,uint offset ){

    endpoint_S endP;

    static uint last_offset_in   = 0;
    static uint last_offset_out  = 0;
    static uint number_point = 1;

    endP.count = count;
    endP.len   = len;
    endP.type  = type;
    endP.num   = 0;
    endP.adress = adress;
    endP.offset_in = offset;

    if(!type){

        endP.offset    = last_offset_in;
        last_offset_in = endP.count*endP.len*number_point;
    }
    else
    {
        endP.offset     = last_offset_out;
        last_offset_out = endP.count*endP.len;
    }
    number_point++;

    endpoint.append(endP);
}

int linux_usb_class::read_data(){

    struct pollfd ufds[1];
    int time_out = 3000;	/* time out for poll */
    int rc;
    uint adress;

    ufds[0].fd = fd;
    ufds[0].events = POLLIN;

    for (;;) {
        if ((rc = poll(ufds, 1, time_out)) < 0)   qDebug() <<"Failure in poll:" << rc << strerror(errno) << "\n";
        if (rc > 0) {
            if (ufds[0].revents & POLLIN) {
                ioctl(fd,DEV_OFFSET_DATA,&adress);

                for(int i=0;i<endpoint.size();i++){
                    if(!endpoint[i].type && endpoint[i].adress == adress){
                        rc = pread(fd, (buffer_in+endpoint[i].len*endpoint[i].num+endpoint[i].offset), endpoint[i].len,endpoint[i].offset_in);
                        endpoint[i].num++;
                        if(endpoint[i].num == endpoint[i].count){
                            endpoint[i].num = 0;
                            emit haveData((buffer_in+endpoint[i].offset),endpoint[i].adress);
                        }
                    }

                }
            }
            else
                qDebug() << "poll timed out in " << time_out <<"milliseconds";
        }
    }
    timer_timeout->start(timeout);
    return rc;
}

void linux_usb_class::sendData(char *data, int len){

     write(fd,data,len);

    return;

}

