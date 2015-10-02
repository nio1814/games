#ifdef Q_OS_WIN32
#include <windows.h>
#include <string.h>
#include <stdio.h>
#endif

void Error(const char *_format, ...)
{
	char text[1024];
	va_list ap;

	va_start(ap, _format);
	vsprintf(text, _format, ap);
	va_end(ap);

	MessageBox(NULL, text, "Error", MB_OK);
}

