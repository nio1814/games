#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL>

class QtLogo;

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    GLWidget(QWidget *parent=0);
    ~GLWidget();

    QSize minimumSizeHint() const;

    float scale;

protected:
    void initializeGL();
    void paintGL();
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
private:
    QSlider* createSlider();
    QtLogo *logo;
    int xRot;
    int yRot;
    int zRot;
    QPoint lastPos;
};

#endif // GLWIDGET_H
