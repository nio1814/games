#ifndef LevelWindow_H
#define LevelWindow_H

#include <qmatrix4x4.h>

#include "glwidget.h"

class Game;

class LevelWindow : public GLWidget
{
    Q_OBJECT
public:
	LevelWindow(QWidget *parent);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void mousePressEvent(QMouseEvent *);
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

#endif // LevelWindow_H

