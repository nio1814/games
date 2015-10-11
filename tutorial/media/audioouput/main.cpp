#include "audiotest.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setApplicationName("Audio Output Test");

	AudioTest w;
	w.show();

	return a.exec();
}
