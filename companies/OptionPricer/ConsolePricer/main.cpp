#include "../common_files/option.h"
#include "../common_files/tree_pricer.h"
#include <iostream>
#include <string>
using namespace std;

std::string der_type_string[] = {
	"EUR_PUT", "EUR_CALL", "AME_PUT", "AME_CALL"
};


int main() {
	// the bigger step is, the more precise the result is.
	// for European options, the tree pricer's result would be closer to BS value
	int step = 100;
	option op(41, 40, .75, .35, .02, .04);
	for (int cnt = DerType::EUR_PUT; cnt <= AME_CALL; cnt++) {
		DerType type = DerType(cnt);
		double res = tirnomial_tree_pricer::calculate(step, type, op);
		cout << "Calculating " << der_type_string[cnt] << endl;
		cout << "Trinomial tree result: " << res << endl;
		if (type == EUR_CALL ) {
			cout << "BS value: " << op.euro_call_BS() << endl;
		} else if (type == EUR_PUT) {
			cout << "BS value: " << op.euro_put_BS() << endl;
		}
		cout << endl;
	}
}