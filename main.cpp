#include "pult_3m1_main_class.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   QFont font("Times new roman");
    font.setStyleHint(QFont::Monospace);
    QApplication::setFont(font);

    QSurfaceFormat format;
    format.setDepthBufferSize(16);
    QSurfaceFormat::setDefaultFormat(format);

    pult_3m1_main_class w;
    w.show();

    return a.exec();
}
