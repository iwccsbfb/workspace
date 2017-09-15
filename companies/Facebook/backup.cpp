#include <vector>
#include <unordered_map>
#include <map>
#include <iostream>
#include <algorithm>


#include <vector>
#include <string>
#include <sstream>
#include <queue>
using namespace std; using namespace std;


struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution3 {
public:
	ListNode* reverseKGroup(ListNode* head, int k) {
		if (k <= 1 || head == nullptr) return head;
		ListNode *prev = head, *p = head->next, *first = head, *last = head;
		if (p == nullptr) return head;

		bool is_first_group = true;
		while (true) {
			int i;
			for (i = 1; i <= k - 1 && p != nullptr; i++) {
				auto tmp = p->next;
				p->next = prev;
				prev = p;
				p = tmp;
			}
			if (i != k) {
				first = prev;
				p = prev->next;
				int cnt = 1;
				while (cnt++ <= i - 1) {
					auto tmp = p->next;
					p->next = prev;
					prev = p;
					p = tmp;
				}
				first->next = nullptr;
				return head;
			}
			if (is_first_group) {
				head = prev;
				is_first_group = false;
			}
			else {
				last->next = prev;
				last = first;
			}
			first->next = p;

			if (p == nullptr) return head;
			first = prev = p;
			p = p->next;
			if (p == nullptr) return head;
		}
	}
};
//auto a = new ListNode(1);
//auto b = new ListNode(2);
//auto c = new ListNode(3);
//auto d = new ListNode(4);
//a->next = b;
//Solution().reverseKGroup(a, 2);


struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
public:

	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		if (!root) return "";
		vector<TreeNode*>v1{ root }, v2;
		string res = std::to_string(root->val) + ",";
		while (true) {
			v2.clear();
			for (auto node : v1) {
				if (node->left)
					v2.push_back(node->left);
				if (node->right)
					v2.push_back(node->right);
			}
			if (v2.empty())
				break;
			for (auto node : v1) {
				if (node->left)
					res += std::to_string(node->left->val);
				res += ",";
				if (node->right)
					res += std::to_string(node->right->val);
				res += ",";
			}
			v1 = std::move(v2);
		}
		res.pop_back();
		return res;
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		stringstream ss(data);
		vector<string> v;
		string val;
		while (getline(ss, val, ',')) {
			v.push_back(val);
		}
		if (v.empty()) return nullptr;
		TreeNode* root = to_TreeNode(v[0]);
		vector<TreeNode*>layer1{ root }, layer2;
		int i = 1;
		while (i < v.size()) {
			// layer1 is not empty, layer2 could have null element
			for (int k = 0; k < layer1.size() * 2 && i < v.size(); k++, i++)
				layer2.push_back(to_TreeNode(v[i]));
			for (int k2 = 0; k2 < layer2.size(); k2++) {
				int idx = k2 / 2;
				if (k2 % 2 == 0) layer1[idx]->left = layer2[k2];
				else layer1[idx]->right = layer2[k2];
			}
			layer1.clear();
			for (auto &node : layer2) {
				if (node) layer1.push_back(node);
			}
			layer2.clear();
		}
		return root;
	}
	inline TreeNode* to_TreeNode(string &s) {
		if (s == "") return nullptr;
		return new TreeNode(stoi(s));
	}
};

// Your Codec object will be instantiated and called as such:
////
//	Codec codec;
//	TreeNode* root = new TreeNode(1);
//	root->right = new TreeNode(2);
//	root->right->left = new TreeNode(3);
//	codec.deserialize(codec.serialize(root));

class Solution2 {
public:
	bool exist(vector<vector<char>>& board, string word) {
		if (board.empty() || board[0].empty() || word.empty()) return false;
		int h = board.size(), w = board[0].size();
		vector<vector<bool>> visited(h, vector<bool>(w, false));
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				if (search(board, visited, i, j, word, 0))
					return true;
			}
		}
		return false;
	}

	bool search(vector<vector<char>>& board, vector<vector<bool>>& visited,
		int i, int j, string word, int start = 0) {
		int h = board.size(), w = board[0].size();
		// the order of this two cannot be changed
		if (start == word.size()) return true;
		if (i < 0 || i >= h || j < 0 || j >= w || visited[i][j]) return false;
		if (board[i][j] != word[start++]) return false;

		visited[i][j] = true;
		bool ret = (search(board, visited, i - 1, j, word, start) ||
			search(board, visited, i + 1, j, word, start) ||
			search(board, visited, i, j - 1, word, start) ||
			search(board, visited, i, j + 1, word, start));
		visited[i][j] = false;
		return ret;
	}
};



class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		unordered_map<int, vector<int>> m;
		for (int i = 0; i < nums.size(); i++)
			m[nums[i]].push_back(i);
		for (auto &i : m) {
			if (m.find(target - i.first) != m.end()) {
				int &a = i.second[0];
				auto &v = m[target - i.first];
				int &b = v.back();
				if (a == b && v.size()==1 ) continue;
				if(a<b) return vector<int> {a, b};
				else return vector<int> {b, a};
			}
		}
	}
	vector<int> twoSum_1(vector<int>& nums, int target) {
		int sz = nums.size();
		auto cp = nums;
		q_sort(cp, 0, sz - 1);
		int i = 0, j = sz - 1;
		while (i<j) {
			int sum = cp[i] + cp[j];
			if (sum == target) break;
			else if (sum < target) i++;
			else j--;
		}
		int l = -1, r = -1;
		for (int tmp = 0; tmp < sz; tmp++)
		{
			if (l == -1 && nums[tmp] == cp[i]) l = tmp;
			else if (r == -1 && nums[tmp] == cp[j]) r = tmp;
		}
		return vector<int>{l, r};
	}

	void q_sort(vector<int> &nums, int s, int e) {
		if (s >= e) return;
		int id = partition(nums, s, e);
		q_sort(nums, s, id - 1);
		q_sort(nums, id + 1, e);
	}

	int partition(vector<int> &nums, int s, int e) {
		int idx = rand() % (e - s) + s;
		std::swap(nums[idx], nums[e]);
		int &pivot = nums[e];
		int res = s;
		for (int i = s; i < e; i++) {
			if (nums[i] <= pivot)
				std::swap(nums[i], nums[res++]);
		}
		std::swap(nums[res], nums[e]);
		return res;
	}
};

