#include <QtGui/QApplication>
#include "ACARSMainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ACARSMainWindow w;
    w.show();

    return a.exec();
}
