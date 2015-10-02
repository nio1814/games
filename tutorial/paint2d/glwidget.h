#ifndef GLWIDGET_H
#define GLWIDGET_H

#if QT_MAJOR_VERSION>4
class GLWidget : public QOpenGLWidget
#else
class GLWidget : public QGLWidget
#endif
{
public:
    GLWidget();

signals:

public slots:
};

#endif // GLWIDGET_H
