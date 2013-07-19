#include <QApplication>
#include <Core/ACARSSystem.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ACARSSystem *System = new ACARSSystem(&a);
    System->Start();

    return a.exec();
}
