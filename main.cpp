#include <QtGui/QApplication>
#include <Core/ACARSCore.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ACARSCore System(&a);
    System.ACARSInit();
    System.ACARSStart();

    return a.exec();
}
