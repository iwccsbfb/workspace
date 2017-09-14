#ifndef CALCULATOR_H
#define CALCULATOR_H
#include "../common_files/option.h"
#include "../common_files/tree_pricer.h"
#include <QtWidgets/QMainWindow>
#include "ui_calculator.h"


class QTCalculator : public QMainWindow
{
	Q_OBJECT
public:
	QTCalculator(QWidget *parent = 0);
	~QTCalculator();

public slots:
	// get values from checkboxes and calculate the result
	void calculate();

	// show About information
	void showAbout();

private:
	Ui::QTCalculatorClass ui;
};



#endif // CALCULATOR_H


