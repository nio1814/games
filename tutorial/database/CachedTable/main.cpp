#include "tableeditor.h"
#include <QApplication>

#include "connection.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	if(!createConnection())
		return 1;

	TableEditor editor("person");
	editor.show();

	return a.exec();
}
