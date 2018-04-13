#ifndef USB_MKO_BC123_CLASS_H
#define USB_MKO_BC123_CLASS_H

#include <QObject>
#include "../opengl/pult.h"
#include "linux_usb_class.h"

class usb_mko_BC123_class : public QObject
{
    Q_OBJECT
public:
    explicit usb_mko_BC123_class(QObject *parent = nullptr);
private:
    linux_usb_class     *usb_mko_BC123;

signals:


public slots:
};

#endif // USB_MKO_BC123_CLASS_H
