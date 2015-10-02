#include "glwidget.h"

#include <QGLFormat>
#include <qtimer.h>

#include "helper.h"

GLWidget::GLWidget(Helper *helper, QWidget *parent)
	: QGLWidget(QGLFormat(QGL::SampleBuffers), parent), helper(helper)
{
    setFixedSize(200, 200);
    setAutoFillBackground(false);
}

void GLWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    helper->paint(&painter, event, elapsed);
    painter.end();
}

void GLWidget::animate()
{
    elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval()) % 1000;
    update();
}
