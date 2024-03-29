#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "light.h"

class Level;
class QElapsedTimer;

#include "QtOpenGL/QGLWidget"
class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    GLWidget(QWidget *parent);
    ~GLWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void restartTimer();
public slots:
    void process();
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
private:
	Level* m_level;
	QElapsedTimer* m_timer;
};

#endif // GLWIDGET_H
