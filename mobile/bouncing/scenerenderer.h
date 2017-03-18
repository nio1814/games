#ifndef SCENERENDERER_H
#define SCENERENDERER_H

#include <QOpenGLFunctions>

class Scene;
class QOpenGLShaderProgram;

#include <qcolor.h>
#include <qsize.h>

class SceneRenderer : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    SceneRenderer(QObject *parent = 0);
	~SceneRenderer();

	void setViewportSize(const QSize &size);
signals:

public slots:
	void paint();

private:
	Scene* m_scene;
	QOpenGLShaderProgram* m_program;

	float m_lastTime;
	QColor m_backgroundColor;
	QSize m_viewportSize;

};

#endif // SCENERENDERER_H
