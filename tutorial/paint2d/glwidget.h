#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <qglobal.h>

class Helper;


#if QT_VERSION>=0x050400
#include <qopenglwidget.h>
class GLWidget : public QOpenGLWidget
#else
#include <QGLWidget>
class GLWidget : public QGLWidget
#endif
{
    Q_OBJECT
public:
    GLWidget(Helper *helper, QWidget *parent);
protected:
    void paintEvent(QPaintEvent *event);

private:
    Helper *helper;
    int elapsed;
signals:

public slots:
    void animate();
};

#endif // GLWIDGET_H
