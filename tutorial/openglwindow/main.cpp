#include "openglwindow.h"
#include <QApplication>

#include "trianglewindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat format;
    format.setSamples(16);

    TriangleWindow w;
//    OpenGLWindow w;
    w.setFormat(format);
    w.resize(640,480);
    w.setAnimating(true);
    w.show();

    return a.exec();
}
