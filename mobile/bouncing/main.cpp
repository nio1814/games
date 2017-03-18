#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qquickview.h>

#include "scene.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

	qmlRegisterType<Scene>("Bouncing", 1, 0, "Scene");

	QQuickView view;
	view.setResizeMode(QQuickView::SizeRootObjectToView);
	view.setSource(QUrl("qrc:/main.qml"));
	view.show();
//	QQmlApplicationEngine engine;
//	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
