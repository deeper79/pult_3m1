#ifndef USB_ADC_RLS_CLASS_H
#define USB_ADC_RLS_CLASS_H

#include <QObject>
#include "linux_usb_class.h"

class usb_adc_rls_class : public QObject
{
    Q_OBJECT
public:
    explicit usb_adc_rls_class(QObject *parent = nullptr);
    void setDeviceName(QString name){device_name = name;}

private:
    linux_usb_class *adc_rls;
    QString          device_name;
signals:
    void haveData(char *buf);

public slots:
};

#endif // USB_ADC_RLS_CLASS_H
