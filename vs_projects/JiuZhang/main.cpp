#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

/*
bool isCorrectPassword(string &pwd) {
	return pwd == "abcdEFG";
}

void helper(string pwd, int start) {
	if (start == pwd.size())
		return;
	if (isCorrectPassword(pwd))
		throw exception(pwd.c_str());
	helper(pwd, start + 1);
	pwd[start] += 'A' - 'a';
	if (isCorrectPassword(pwd))
		throw exception(pwd.c_str());
	helper(pwd, start + 1);
}

string testPwd(string pwd) {
	// if (pwd.empty()) return isCorrectPassword(pwd);
	for (int i = 0; i < pwd.size(); i++) {
		for (int j = 0; j < i; j++) {
			string s = pwd.substr(j, i - j + 1);
			try {
				helper(s, 0);
			}
			catch (exception e) {
				return e.what();
			}
		}
	}
}

typedef pair<vector<int>*, int> mypair; //array, idx
struct myCompare {
	bool operator()(mypair const &a, mypair const &b) const {
		// return v1[idx1] < v2[idx2]
		return (*(a.first))[a.second] < (*(b.first))[b.second];
	}
};
vector<int> mergekSortedArrays(vector<vector<int>>& arrays) {
	vector<int> res;
	priority_queue<mypair, vector<mypair>, myCompare  > q;
	for (auto &arr : arrays) {
		if (!arr.empty())
			q.push(std::make_pair(&arr, 0));
	}
	while (!q.empty()) {
		vector<int>* v = q.top().first;
		int idx = q.top().second;
		q.pop();
		res.push_back((*v)[idx]);
		if (idx < v->size()) {
			q.push(std::make_pair(v, idx + 1));
		}
	}
	return res;
}

struct mycompare {
	bool operator()(int const&a, int const&b) const {
		return a < b;
	}
};

int main()
{
	vector<vector<int>> v{ vector<int>{1, 3, 5, 7},
		vector<int>{2, 4, 6}, vector<int>{0, 8, 9, 10, 11} };
	// auto res = mergekSortedArrays(v);
	vector<int> v{ 1,5,6,4,8,7,3,9 };
	std::sort(v.begin(), v.end(), mycompare());

	std::array<int, 10> s = { 5, 7, 4, 2, 8, 6, 1, 9, 0, 3 };

	// sort using a custom function object
	struct {
		bool operator()(int a, int b)
		{
			return a < b;
		}
	} customLess;
	std::sort(s.begin(), s.end(), customLess);

	return 0;
}
*/



int main() {

	return 0;
}