#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtGlobal>
#include <qmatrix4x4.h>

#if (QT_VERSION >= 0x050500)
#include "qopenglwidget.h"
class GLWidget : public QOpenGLWidget
#else
#include "QtOpenGL/QGLWidget"
class GLWidget : public QGLWidget
#endif
{
    Q_OBJECT
public:
    GLWidget(QWidget *parent);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL(); Q_DECL_OVERRIDE;
private:
    int m_elapsed;
    QMatrix4x4 m_projection;
signals:

public slots:
    void animate();
};

#endif // GLWIDGET_H
