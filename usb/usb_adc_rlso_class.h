#ifndef USB_ADC_RLSO_CLASS_H
#define USB_ADC_RLSO_CLASS_H

#include <QObject>
#include "../usb/linux_usb_class.h"

class usb_adc_rlso_class : public QObject
{
    Q_OBJECT
public:
    explicit usb_adc_rlso_class(QObject *parent = nullptr);

    void setDeviceName(QString name){device_name = name;}

private:
    linux_usb_class *adc_rlso;
    QString          device_name;

signals:

public slots:
};

#endif // USB_ADC_RLSO_CLASS_H
