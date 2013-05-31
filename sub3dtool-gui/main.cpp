#include "sub3dtoolgui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    sub3dtoolgui w;
    w.show();
    
    return a.exec();
}
