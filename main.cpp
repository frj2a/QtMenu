// "$Date: 2019-01-08 21:47:32 -0200 (ter, 08 jan 2019) $"
// "$Author: chico $"
// "$Revision: 3 $"

#include <QApplication>
#include "CGMenu.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CGMenu w;
	a.setStyle ( "Cleanlooks" );
	w.show();

	return a.exec();
}

//	estilos: Motif , Cleanlooks , Plastique , Cde
