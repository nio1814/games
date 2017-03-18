#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "squircle.h"
#include <qquickview.h>

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	qmlRegisterType<Squircle>("SceneGraph", 1, 0, "Squircle");

	QQuickView view;
	view.setResizeMode(QQuickView::SizeRootObjectToView);
	view.setSource(QUrl("qrc:/main.qml"));
	view.show();

//	QQmlApplicationEngine engine;
//	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

	return app.exec();
}
