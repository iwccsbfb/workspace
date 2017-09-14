//============================================================================
// Name        : TS2.cpp
// Author      : Billy
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>
#include <functional>
#include <list>
#include <deque>
//#include <stdio.h>
using namespace std;




#include "header.h"

int main() {
	//test_wildcard();
	//cout << (1 & 0X5555555555555555) << endl;
	deque<int>d;
//printf("abc %.4f %s", 12.123456, "ef");
	// run_multi_thread();
	return 0;
}




bool is_prime_num(int num, vector<int> &nums) {
  float tmp = sqrt(num);
  // if any prime number is a factor of val, it is not prime
  for (auto val : nums) {
    if (val >= tmp) return true;
    if (num % val == 0)
      return false;
  }
  return false;
}

vector<int> get_prime_num(int n) {
  vector<int> res;
  if (n < 2) return res;
  res.push_back(2);
  for (int i = 3; i <= n; i++) {
    if (is_prime_num(i, res))
      res.push_back(i);
  }
  return res;
}
