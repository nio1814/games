#include "glwidget.h"

GLWidget::GLWidget(Helper *helper, QWidget *parent)
	: QGLWidget(QGLFormat(QGL::SampleBuffers), parent), helper(helper)
{
}
