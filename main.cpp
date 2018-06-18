#include "dose.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dose w;
    w.show();

    return a.exec();
}
