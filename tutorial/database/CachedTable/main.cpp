#include "tableeditor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TableEditor w;
	w.show();

	return a.exec();
}
