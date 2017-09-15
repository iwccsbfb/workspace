#include "calculator.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTCalculator w;
	w.setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
	w.show();
	return a.exec();
}
