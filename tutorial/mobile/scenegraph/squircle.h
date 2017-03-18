#ifndef SQUIRCLE_H
#define SQUIRCLE_H

#include <QQuickItem>

class SquircleRenderer;

class Squircle : public QQuickItem
{
	Q_OBJECT
	Q_PROPERTY(qreal t READ t WRITE setT NOTIFY tChanged)
public:
	Squircle();

	qreal t() const;
	void setT(qreal t);

signals:
	void tChanged();

public slots:
	void sync();
	void cleanup();
private slots:
	void handleWindowChanged(QQuickWindow* win);
private:
	qreal m_t;
	SquircleRenderer* m_renderer;
};

#endif // SQUIRCLE_H
