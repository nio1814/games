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

	return a.exec();
}
