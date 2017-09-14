#include "calculator.h"
#include <iostream>
#include <QMessageBox>

QTCalculator::QTCalculator(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

QTCalculator::~QTCalculator()
{

}

void QTCalculator::calculate() {
	int a = 1;
	auto S0 = ui.doubleSpinBox_S0->value(),
		K = ui.doubleSpinBox_K->value(),
		T = ui.doubleSpinBox_T->value(),
		sigma = ui.doubleSpinBox_sigma->value(),
		q = ui.doubleSpinBox_q->value(),
		r = ui.doubleSpinBox_r->value();
	option op(S0, K, T, sigma, q, r);
	// logic depends on the UI? 
	DerType der = DerType(DerType::EUR_PUT + ui.comboBox_derType->currentIndex());
	int steps = ui.spinBox_steps->value();
	double tree_val = tirnomial_tree_pricer::calculate(steps, der, op);
	
	string text = "Trinomial tree value is :" + std::to_string(tree_val) + "\n\n";
	if (der == DerType::EUR_CALL) {
		double bs_val = op.euro_call_BS();
		text += "BS value is: " + std::to_string(bs_val) + "\n\n";
	}
	else if (der == DerType::EUR_PUT) {
		double bs_val = op.euro_put_BS();
		text += "BS value is: " + std::to_string(bs_val) + "\n\n";
	}
	ui.textBrowser_display->setPlainText(QString::fromStdString(text));
}

void QTCalculator::showAbout() {
	QMessageBox::about(this, "About", "This trinomial tree option pricer is developed by Arthur Wang, for Alphadyne's test.");
}