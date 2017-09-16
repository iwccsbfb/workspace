// - Reverse Polish Notation
// use XML/JSON serialization to allow client side configuration, e.g. add a new operator
#include <iostream>
#include <string>
#include <stack>
#include <exception>
#include <sstream>
#include <unordered_map>
#include <stdexcept>
#include <vector>

using namespace std;

double add(double a, double b) {
    return a + b;
}

double minus(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    return a / b;
}


// operator string to function pointer
//unordered_map<string, double(*)(double, double)> m;
unordered_map<string, void*> m;

int main() {
    m["+"] = (void*)&add;
    m["-"] = (void*)&::minus;
    m["*"] = (void*)&multiply;
    m["/"] = (void*)&divide;
    vector<string> rpn = {"4", "5", "13", "/", "+"};
    stack<double> s;
    for(auto &str: rpn) {
	// str is an operator
	if(m.find(str) != m.end()) {
	    double b = s.top(); s.pop();
	    double a = s.top(); s.pop();
	    double res = (reinterpret_cast<double(*)(double, double)>(m[str]) )(a,b);
	    //double res = m[str](a, b);
	    s.push(res);
	} else {
	    s.push(stod(str));
	}
    }
    if(s.size() != 1) throw string("incorrect rpn");
    cout << s.top() << endl;
//    RPNCalculator c;
//    cout << c.calculate(f) << endl;

    return 0;
}
