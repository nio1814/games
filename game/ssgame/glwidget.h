#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtGlobal>
#include <qmatrix4x4.h>

class Game;

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
    void paintGL();
private:
    Game *m_game;
    int m_elapsed;
    QMatrix4x4 m_projection;
    QMatrix4x4 m_model;
    GLfloat m_aspectRatio;
signals:

public slots:
    void animate();
};

#endif // GLWIDGET_H
