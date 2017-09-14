#include <vector>
#include <iostream>
using namespace std;


int maxSubArray(vector<int> &nums) {
	int max_sum = numeric_limits<int>::min();
	//int start = 0;
	int sum = 0;
	bool flag = true; //whether start has been renewed
	for (int end = 0; end < nums.size(); end++) {
		if (flag)
			sum = nums[end];
		else
			sum += nums[end];

		if (sum > max_sum)
			max_sum = sum;

		if (sum <= 0)
			flag = true; //start = end + 1;
		else
			flag = false;
	}
	return max_sum;
}
//cout << maxSubArray(vector<int>{2, 1, -3, 4, -1, 2, 1, -5, 4});

//max sub matrix TODO



#include <queue>
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
	//even k<=nums.size(); nums could be empty
	if (nums.empty()) return vector<int>();

	typedef pair<int, int> _pair;
	priority_queue<_pair> Q;
	vector<int> result(nums.size() - k + 1);
	for (int i = 0; i < k; i++)
		Q.push(_pair(nums[i], i));

	for (int i = k; i < nums.size(); i++) {
		_pair top = Q.top();
		result[i - k] = top.first;


		Q.push(_pair(nums[i], i));

		//if Q.size == 1, after popping once, would fail; so put push beforehand
		//while (!Q.empty() && Q.top().second <= i - k)
		while (Q.top().second <= i - k)
			Q.pop();
	}
	_pair top = Q.top();
	*(result.end() - 1) = top.first;
	return result;
}
//vector<int> a = maxSlidingWindow(vector<int>{1, -1}, 1);

//output permutation.  Nov. 1st, 2015
vector<vector<char>> get_permutation(string s) {
	vector<vector<char>> result;
	if (s.size() == 1) {
		result.push_back(vector<char>{s[0]});
		return result;
	}
	for (int i = 0; i < s.size(); i++) {
		string s_copy = s;
		char e = s[i];
		s_copy[i] = s_copy[s.size() - 1];
		//s_copy[s.size() - 1] = e;
		string sub_arr = s_copy.substr(0, s.size() - 1);
		vector<vector<char>> res = get_permutation(sub_arr);
		for (auto i : res) {
			i.push_back(e);
			result.push_back(i);
		}
	}
	return result;
}

void test_get_permutation() {
	vector<vector<char>> v = get_permutation("abcde");
	for (auto i : v) {
		for (auto j : i)
			cout << j;
		cout << endl;
	}
}

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
	int h = obstacleGrid.size();
	if (h == 0) return 0;
	int w = obstacleGrid[0].size();
	if (w == 0) return 0;
	vector<int> v(w);
	v[0] = (obstacleGrid[0][0] == 0) ? 1 : 0;
	for (int i = 1; i<w; i++)
		v[i] = (obstacleGrid[0][i] == 0) ? v[i - 1] : 0;

	for (int j = 1; j<h; j++) {
		if (obstacleGrid[j][0] == 1)   v[0] = 0;
		for (int i = 1; i<w; i++)
			v[i] = (obstacleGrid[j][i] == 0) ? v[i - 1] + v[i] : 0;
	}
	return v[w - 1];
}
//cout << uniquePathsWithObstacles(vector<vector<int>>{vector<int>{0}});


//huajun15868@gmail.com
//smart pointer;
class U_Ptr {
	friend class H;
private:
	int *ip;
	size_t use;
	U_Ptr(int *p) :ip(p), use(1) {}
	~U_Ptr() { delete ip; }
};

class H {
public:
	H(int *p, int i) : ptr(new U_Ptr(p)), value(i) {}
	H(const H&org) : ptr(org.ptr), value(org.value) { ++ptr->use; }
	H & operator=(const H& rhs) {
		++rhs.ptr->use;
		if (--ptr->use == 0)
			delete ptr;
		ptr = rhs.ptr;
		value = rhs.value;
		return *this;
	}
	~H() {
		if (--ptr->use == 0)
			delete ptr;
	}
private:
	//pointer to counter
	U_Ptr *ptr;
	int value;
};
void test_smart_pointer() {
	int *p = new int[10];
	for (int i = 0; i < 10; i++)
		p[i] = i;

	H p1(p, 10);
	H p2(p1);
}