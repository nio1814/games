#include "glwidget.h"

#if (QT_VERSION >= 0x050500)
GLWidget::GLWidget(QWidget *parent)
        : QOpenGLWidget(parent)
#else
        : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
#endif
{
}
