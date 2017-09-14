#include <set>
#include<iostream>
#include <assert.h>
#include <vector>
#include <tuple>
using namespace std;

class Solution_single_num2 {
public:
	int singleNumber(vector<int>& nums) {
		int result = 0;
		for (int i = 0; i < sizeof(int) * 8; i++) {
			int sum = 0;
			for (vector<int>::iterator it = nums.begin(); it < nums.end(); it++)
			{
				sum += 1 & ((*it) >> i);
			}
			result |= ((sum % 3) << i);
		}
		return result;
	}
};


class Solution_single_num3 {
public:
	std::tuple<int, int> singleNumber(vector<int>& nums) {
		int a = 0, b = 0, c = 0;
		for (vector<int>::iterator it = nums.begin(); it < nums.end(); it++)
			c ^= *it;
		int cnt = 0;
		while ((c&(1 << cnt)) == 0) cnt++;
		for (vector<int>::iterator it = nums.begin(); it < nums.end(); it++)
		{
			if (*it & (1 << cnt)) {
				a ^= *it;
			}
		}
		b = a^c;
		return std::make_tuple(a, b);
	}
};


template<typename T>
void output_bits(T a) {
	int len = sizeof(a) << 3;
	for (int i = len - 1; i >= 0; i--)
		cout << ((a >> i) & 1) << ((len - i) % 8 == 0 ? "-" : "");
	cout << endl;
}
uint32_t reverseBits(uint32_t n) {
	return uint32_t(uint64_t(1 << 32) - uint64_t(1) - uint64_t(n));
}
char reverse_char(char &a) {
	char b = 0;
	output_bits<char>(a);
	for (int i = 0; i < 8; i++) {
		b |= ((1 & (a >> i)) << (7 - i));
	}
	output_bits<char>(b);
	return b;
}
uint32_t reverseBits_2(uint32_t n) {
	char *ch = reinterpret_cast<char*>(&n), tmp;

	tmp = ch[0];
	ch[0] = reverse_char(ch[3]);
	ch[3] = reverse_char(tmp);

	tmp = ch[1];
	ch[1] = reverse_char(ch[2]);
	ch[2] = reverse_char(tmp);
	return n;
}
uint32_t reverseBits_3(uint32_t n) {
	uint32_t b = 0;
	for (int i = 0; i < 32; i++) {
		b |= ((1 & (n >> i)) << (31 - i));
	}
	return b;
}


#include <string>
//alen's question;
//find the chars that are in str1, but not in its subset str2
void find_chars(string s1, string s2) {
	size_t i = 0, j = 0;
	while (i < s1.size() && j < s2.size()) {
		if (s1[i] != s2[j]) {
			cout << s1[i++];
		}
		else { //s1[i] == s2[j]
			i++; j++;
		}
	}
	while (i < s1.size())
		cout << s1[i++];
}

int removeElement(vector<int>& nums, int val) {
	if (nums.empty())	return 0;
	int bgn = 0;
	//nums.size()-1
	while (bgn < nums.size()) {
		//while (!nums.empty() && nums.back() == val)
		//	nums.pop_back();
		//if (nums.empty() || bgn >= nums.size() ) return nums.size();
		while (bgn < nums.size() && nums[bgn] == val) {
			nums[bgn] = nums.back();
			nums.pop_back();
		}
		bgn++;
	}
	return nums.size();
}

//check if a 10-digit sequence satisfy the condition
bool check_10_digit_sequence(vector<int>&nums) {
	return false;
}


int uniquePaths(int m, int n) {
	//factorial would overflow, even using long long int
	//num and den must be float, and returning value should be rounded

	//denotes numerator, denominator
	double num = m + n - 2, den = n - 1;
	double result = 1;
	for (int i = 1; i <= n - 1; i++) {
		result *= num / den;
		num--;
		den--;
	}
	//round to the nearest integer
	int res = result;
	if (res + 0.5 <= result)	res++;
	return res;
}

class T {
public:
	int num;
	T(int a) :num(a) { cout << "constructor\n"; }
	//T(T &t1) { cout << "copy constructor\n"; }
	T & operator = (T& t1) {
		cout << "=\n";
		return t1;
	}
};

#include <set>
#include <map>
#include <unordered_map>

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	vector<string> binaryTreePaths(TreeNode* root) {
		vector<string> paths;
		if (root == nullptr) return paths;
		string s = std::to_string(root->val);
		if (!root->left && !root->right) {
			paths.push_back(s);
			return paths;
		}
		recur_get_path(root, s, paths);
		return paths;
	}
	
	void recur_get_path(TreeNode* node, string s, vector<string> &paths) {
		if(node->left)
			recur_get_path(node->left, s + "->" + std::to_string(node->left->val), paths);
		if (node->right)
			recur_get_path(node->right, s + "->" + std::to_string(node->right->val), paths);
		if (!node->left && !node->right)
			paths.push_back(s);
	}
};

#include <queue>
int main() {
	vector<pair<int, int>> v({
	{ 0,1 }, { 0,2 }, { 0,3 }, { 2,4 }, { 0,5 }, { 5,6 }, { 6,7 }, { 2,8 }, { 7,9 }
	});
	auto res = Solution().findMinHeightTrees(10, v);

	return 0;
}
