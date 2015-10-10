#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL>

class GLWidget : public QGLWidget
{
public:
    GLWidget(QWidget *parent=0, QGLWidget *shareWidget=0);
    ~GLWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void rotateBy(int xAngle, int yAngle, int zAngle);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent *event);
//    bool event(QEvent *event);

signals:

public slots:
private:
    void makeObject();

    int xRot;
    int yRot;
    int zRot;
    GLfloat zPos;
    float scale;
    QPoint lastPos;

    GLuint textures[6];
    QVector<QVector3D> vertices;
    QVector<QVector2D> texCoords;

    QMatrix4x4 m_projection;
    QMatrix4x4 m_view;
};

#endif // GLWIDGET_H
