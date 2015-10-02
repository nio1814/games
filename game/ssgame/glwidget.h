#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtGlobal>
#include <QMatrix4x4>

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
private:
    QMatrix4x4 m_projection;
signals:

public slots:

};

#endif // GLWIDGET_H
