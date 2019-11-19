#include "CarPanoramaStitch.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CarPanoramaStitch w;
	w.show();
	return a.exec();
}
