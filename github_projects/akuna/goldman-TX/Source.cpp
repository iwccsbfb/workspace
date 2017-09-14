#include <iostream>
#include <vector>
using namespace std;



#include <limits>
int secondSmallest(vector <int > x) {
	int n = x.size();
	if (x.size() < 2) return 0;
	int first = numeric_limits<int>::max(), second = numeric_limits<int>::max();
	for (auto i : x) {
		// If smaller than first, then update both first and second
		if (i < first) {
			second = first;
			first = i;
		}
		// If between first and second,  then update second 
		else if (i < second)
			second = i;
	}
	return second;
}


#include <assert.h>

long countSteps(int n) {
	assert(n >= 0);
	if (n == 0) return 0;
	long results[3];
	results[0] = results[1] = 1;
	results[2] = 2;
	for (int i = 3; i <= n; i++) {
		results[i % 3] = results[(i - 1) % 3] + results[(i - 2) % 3] + results[(i - 3) % 3];
	}
	return results[n % 3];
}


#include <iostream>
#include <vector>
using namespace std;


#include <unordered_map>
#include <string>
string firstUniqueChar(string input) {
	if (input.size() == 0) return "";
	
	unordered_map<char, int> count;
	for (auto ch : input) count[ch] ++;
	for (auto ch : input)
		if (count[ch] == 1 ){
			return string(1, ch);
		}
}


#include <algorithm>
int sumK(int k, vector<int> nums) {
	std::sort(nums.begin(), nums.end());
	int count = 0;
	for (int i = 0, j = nums.size() - 1; i < j;) {
		int tmp = nums[i] + nums[j];
		if (tmp < k) i++;
		else if (tmp > k) j--;
		else { // tmp == k
			count++;
			if (nums[i] == nums[i + 1]) i++;
			else if (nums[j] == nums[j - 1]) j--;
			else {
				i++; j--;
			}
		}
	}
	return count;
}

int main() {
	cout << int('e') << endl;
	cout << firstUniqueChar("abcebca") << endl;

	//vector<int> nums{ 1,1,5,2, 0, 3,3 };
	//cout << sumK(3, nums) << endl;

	return 0;
}