#ifndef SQUIRCLERENDERER_H
#define SQUIRCLERENDERER_H

#include <qopenglfunctions.h>
#include <qsize.h>

class QOpenGLShaderProgram;

class SquircleRenderer : public QObject, protected QOpenGLFunctions
{
	Q_OBJECT
public:
	SquircleRenderer(QObject *parent = 0);
	~SquircleRenderer();

	void setT(qreal t);
	void setViewportSize(const QSize& size);

signals:

public slots:
	void paint();
private:
	qreal m_t;
	QSize m_viewportSize;
	QOpenGLShaderProgram* m_program;
};

#endif // SQUIRCLERENDERER_H
