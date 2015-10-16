#include "remoteselector.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RemoteSelector w;
    w.show();

    return a.exec();
}
