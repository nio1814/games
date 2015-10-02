#ifndef TRIANGLEWINDOW_H
#define TRIANGLEWINDOW_H

#include "openglwindow.h"

#include <qopenglshaderprogram.h>

class TriangleWindow : public OpenGLWindow
{
public:
    TriangleWindow();

    void initialize() Q_DECL_OVERRIDE;
    void render() Q_DECL_OVERRIDE;

signals:

public slots:

private:
    GLuint loadShader(GLenum type, const char* source);

    QOpenGLShaderProgram *m_program;
    int m_frame;

    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;
};

#endif // TRIANGLEWINDOW_H
