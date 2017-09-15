#include <vector>
#include <unordered_map>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;


class TreeNode {
public:
	int val;
	TreeNode *left, *right;
	TreeNode(int val) {
		this->val = val;
		this->left = this->right = NULL;
	}
};

vector<int> postorderTraversal(TreeNode *root) {
	// write your code here
	if (root == nullptr) return vector<int>();
	vector<int> res;
	vector<TreeNode*>s{ root };
	TreeNode *p = nullptr, *prev = nullptr;
	while (!s.empty()) {
		p = s.back();
		if ((p->left == nullptr && p->right == nullptr) ||
			(p->right != nullptr && prev == p->right) ||
			(p->right == nullptr && p->left != nullptr && prev == p->left)) {
			res.push_back(p->val);
			s.pop_back();
			prev = p;
		}
		else {
			if (p->right != nullptr)
				s.push_back(p->right);
			if (p->left != nullptr)
				s.push_back(p->left);
		}
	}
	return res;
}


bool helper(TreeNode *node, int &height) {
	if (node == nullptr) {
		height = 0; return true;
	}
	int l_height, r_height;
	bool left_balanced = helper(node->left, l_height);
	if (!left_balanced) return false;
	bool right_balanced = helper(node->right, r_height);
	if (!right_balanced) return false;
	if (abs(l_height - r_height) > 1) return false;
	height = max(l_height, r_height) + 1;
	return true;
}

bool isBalanced(TreeNode *root) {
	int height;
	return helper(root, height);
}



//void findPath(TreeNode *root, TreeNode *A, vector<TreeNode*> &li) {
//	li.push_back(root);
//	while (true) {
//		auto p = li.back();
//		while (p->left != nullptr) {
//			li.push_back(p->left);
//			p = p->left;
//		}
//		if (p->right != nullptr) {
//			li.push_back(p->right);
//		}
//
//		if (p == A) {
//			li = std::move(s);
//			return;
//		}
//	}
//}

void findPath(TreeNode *root, TreeNode *A, vector<TreeNode*> &li) {
	if (root == nullptr) return;
	if (root == A) {
		li.push_back(A);
		return;
	}
	vector<TreeNode*> l1, l2;
	findPath(root->left, A, l1);
	if (!l1.empty()) {
		li = std::move(l1); li.push_back(root);
		return;
	}
	findPath(root->right, A, l2);
	if (!l2.empty()) {
		li = std::move(l2);
		li.push_back(root);
		return;
	}
}
TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *A, TreeNode *B) {
	vector<TreeNode*> l1, l2;
	findPath(root, A, l1);
	findPath(root, B, l2);
	reverse(l1.begin(), l1.end());
	reverse(l2.begin(), l2.end());
	int sz = min(l1.size(), l2.size());
	int i;
	for (i = 0; i < sz && l1[i] == l2[i]; i++);
	return l1[i - 1];
}

// if only A, return A; if only B, return B;
//TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *A, TreeNode *B) {
//	// write your code here
//	if (root == nullptr) return nullptr;
//	if (root == A || root == B) return root;
//
//	auto left = lowestCommonAncestor(root->left, A, B);
//	auto right = lowestCommonAncestor(root->right, A, B);
//	if (left != nullptr && right != nullptr)
//		return root;
//	if (left != nullptr)
//		return left;
//	if (right != nullptr)
//		return right;
//	return nullptr;
//}

struct ReturnType {
	int maxPathWithRoot;
	int maxPath;
	ReturnType(int _maxPathWithRoot, int _maxPath) :
		maxPathWithRoot(_maxPathWithRoot), maxPath(_maxPath)
	{}
};

ReturnType helper(TreeNode *root) {
	if (root == nullptr) return ReturnType(root->val, INT_MIN);
	ReturnType r1 = helper(root->left),
		r2 = helper(root->right);
	int maxWithRoot = max(r1.maxPathWithRoot, r2.maxPathWithRoot) + root->val;
	if (maxWithRoot < 0) maxWithRoot = 0;
	int maxPath = r1.maxPathWithRoot + r2.maxPathWithRoot + root->val;
	maxPath = max(max(r1.maxPath, r2.maxPath), maxPath);
	return ReturnType(maxWithRoot, maxPath);
}

int maxPathSum(TreeNode *root) {
	return helper(root).maxPath;
}

#include <string>

int strStr(string haystack, string needle) {
	if (needle.empty()) return 0;
	int sz1 = haystack.size(), sz2 = needle.size();
	for (int i = 0; i <= sz1 - sz2; i++) {
		if (haystack[i] == needle[0]) {
			bool flag = true;
			for (int j = 1; j < sz2; j++)
				if (needle[j] != haystack[i + j]) {
					flag = false;
					break;
				}
			if (flag) return i;
		}
	}
	return -1;
}

int maxPathSum2(TreeNode *root) {
	// Write your code here
	if (root == nullptr) return 0;

}

enum Compare {
	SMALLER, BIGGER
};
// if tree of root is smaller than val; 
bool helper(TreeNode *root, int &val, Compare c) {
	if (root == nullptr) return true;
	bool flag;
	flag = helper(root->left, root->val, SMALLER);
	if (!flag) return false;
	flag = helper(root->right, root->val, BIGGER);
	if (!flag) return false;

	if (c == SMALLER) {
		if (root->val >= val) return false;
		flag = helper(root->right, val, SMALLER);
		if (!flag) return false;
	}
	else {
		if (root->val <= val) return false;
		flag = helper(root->left, val, BIGGER);
		if (!flag) return false;
	}
	return true;
}
bool isValidBST(TreeNode *root) {
	// write your code here
	if (root == nullptr) return true;
	return helper(root->left, root->val, SMALLER) &&
		helper(root->right, root->val, BIGGER);
}


int minSubArrayLen(int s, vector<int>& nums) {
	int sz = nums.size();
	int le = 0, ri = 0, sum = 0, res = INT_MAX;
	while (ri < sz) {
		while (sum < s && ri < sz) {
			sum += nums[ri++];
		}
		while (sum >= s) {
			res = min(res, ri - le);
			sum -= nums[le++];
		}
	}
	return res = (res == INT_MAX) ? 0 : res;
}

vector<string> letterCombinations(string digits) {
	const string letters[] = { "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
	vector<string>res{ "" };
	for (int i = 0; i<digits.size(); i++) {
		vector<string> res2;
		for (auto &str : res) {
			for (auto &letter : letters[i])
				res2.push_back(str + letter);
		}
		res = std::move(res2);
	}

	if (res.size() == 1) return vector<string>();
	return res;
}


string minWindow(string s, string t) {
	if (s.empty()) return "";
	// v1: letter cnt in the window; v2: letter cnt needed
	vector<int> v1(256, 0), v2(256, 0);
	for (char &ch : t)
		v2[(unsigned char)ch]++;
	int sz = s.size(), sz2 = t.size(), cnt = 0;
	int res_start = INT_MIN, res_end = INT_MIN, res_len = INT_MAX;
	for (int start = 0, end = 0; end<sz; end++) {
		int tmp = (unsigned char)(s[end]);
		if (v1[tmp]++ < v2[tmp])
			cnt++;

		while (cnt == sz2) {
			int len = end - start + 1;
			if (len < res_len) {
				res_len = len;
				res_start = start;
				res_end = end;
			}
			int tmp2 = (unsigned char)(s[start++]);
			if (v2[tmp2] != 0 && v1[tmp2]-- >= v2[tmp2]) {
				cnt--;
			}
		}
	}
	if (res_len == INT_MAX) return "";
	return s.substr(res_start, res_len);
}

int minPathSum(vector<vector<int> > &grid) {
	// write your code here
	if (grid.empty()) return 0;
	int m = grid.size(), n = grid[0].size();
	vector<int> res(n, 0);
	res[0] = grid[0][0];
	for (int j = 1; j<n; j++) {
		res[j] = res[j - 1] + grid[0][j];
	}
	for (int i = 1; i<m; i++) {
		res[0] += grid[i][0];
		for (int j = 1; j<n; j++) {
			res[j] = min(res[j], res[j - 1]) + grid[i][j];
		}
	}
	return res.back();
}

int main() {
	vector<vector<int> > grid{ {1,3,1},{1,5,1},{4,2,1} };
	auto res = minPathSum(grid);
	return 0;
}

