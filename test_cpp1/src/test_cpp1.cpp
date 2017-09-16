//============================================================================
// Name        : test_cpp1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

int main() {
	vector <int> v{1,2,3};
	for(auto i: v)
		cout << i << endl;
	cout << "!!!Hello World2!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
