#include "mainwindow.h"
#include <QApplication>

#include "levelwindow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	QPointer<LevelWindow> levelWindow(new LevelWindow(&w));
	w.setCentralWidget(levelWindow.data());
	w.show();

	QPointer<QTimer> timer(new QTimer(&w));
	QObject::connect(timer, SIGNAL(timeout()), levelWindow, SLOT(update()));
	timer->start(10);

	return a.exec();
}
