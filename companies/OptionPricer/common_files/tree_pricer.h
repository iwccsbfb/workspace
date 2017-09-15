#ifndef _TREE_PRICER_H_
#define _TREE_PRICER_H_
#include "option.h"
using namespace std;

// static pricer class
class tirnomial_tree_pricer {
private:
	// get the instrinsic value of the option
	static double get_instrinsic_value(double St, DerType der_type, option &op);
public:
	// calculate function; 
	// the bigger step is, the more precise the result is.
	// For European options, the tree pricer's result would be closer to BS value
	static double calculate(int steps, DerType der_type, option &op);
};

#endif