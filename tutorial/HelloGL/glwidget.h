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

signals:
    void xRotationChanged(int angle);
public slots:
    void setXRotation(int angle);
private:
    QSlider* createSlider();
    QtLogo *logo;
    int xRot;
    int yRot;
    int zRot;
};

#endif // GLWIDGET_H
