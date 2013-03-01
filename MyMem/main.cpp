#include <QtGui/QApplication>
#include "mymem.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyMem w;
    w.show();
    
    return a.exec();
}
