#include <iostream>
#include <vector>
#include <deque>
#include <unordered_set>
#include <string>
#include <algorithm>
using namespace std;

class TrieNode {
public:
	TrieNode() {
		for (int i = 0; i < 26; i++)
			next[i] = NULL;
		isString = false;
	}
	TrieNode *next[26];
	bool isString;
};

class Trie {
public:
	Trie() {
		root = new TrieNode();
	}

	// Inserts a word into the trie.
	void insert(string word) {
		TrieNode *p = root;
		for (int i = 0; i < word.size(); i++) {
			if (p->next[word[i] - 'a'] == NULL) {
				p->next[word[i] - 'a'] = new TrieNode();
			}
			p = p->next[word[i] - 'a'];
		}
		p->isString = true;
	}

	// Returns if the word is in the trie.
	bool search(string word) {
		TrieNode *p = root;
		for (int i = 0; i < word.size(); i++) {
			if (p == NULL) return false;
			p = p->next[word[i] - 'a'];
		}
		if (p == NULL || p->isString == false) return false;
		return true;

	}

	// return longest first
	vector<string> find_prefix_strings(string str) {
		vector<string> res;
		TrieNode *p = root;
		for (int i = 0; i < str.size(); i++) {
			p = p->next[str[i] - 'a'];
			if (p == NULL) break;
			if (p->isString) res.push_back(str.substr(0, i + 1));
		}
		std::reverse(res.begin(), res.end());
		return res;
	}

private:
	TrieNode* root;
};



vector<deque<string>> helper(string target, Trie &trie, bool exclude_target = false) {
	vector<string> prefixes = trie.find_prefix_strings(target);
	vector<deque<string>> res;
	if (target == "") res.push_back(deque<string>());
	for (auto str : prefixes) {
		if (exclude_target && str == target) continue;

		string sub_target = target.substr(str.size());
		vector<deque<string>> sub_res = helper(sub_target, trie);
		if (!sub_res.empty()) {
			// only return the longer result
			for (auto v : sub_res) {
				v.push_front(str);
				res.push_back(v);
			}
			break;
		}
	}
	return res;
}

string restore_spaces(const string& inputString, const vector <string>& dictionary) {
	Trie trie;
	for (auto &word : dictionary)
		trie.insert(word);

	vector<deque<string>> res = helper(inputString, trie);
	string result;
	for (auto &d : res) {
		for (auto &s : d)
			result += s + " ";
	}

}


vector<deque<string>> helper(string target, Trie &trie, bool exclude_target = false) {
	vector<string> prefixes = trie.find_prefix_strings(target);
	vector<deque<string>> res;
	if (target == "") res.push_back(deque<string>());
	for (auto str : prefixes) {
		if (exclude_target && str == target) continue;

		string sub_target = target.substr(str.size());
		vector<deque<string>> sub_res = helper(sub_target, trie);
		if (!sub_res.empty()) {
			// only return the longer result
			for (auto v : sub_res) {
				v.push_front(str);
				res.push_back(v);
			}
			break;
		}
	}
	return res;
}

void build_string(const std::string target, const std::unordered_set<std::string> &dictionary, std::string &result) {
	Trie trie;
	for (auto &word : dictionary)
		trie.insert(word);

	vector<deque<string>> res = helper(target, trie, true);
	vector<string> words;
	for (auto &d : res) {
		for (auto &s : d)
			words.push_back(s);
	}

	bool target_in_dict = false;
	if (trie.search(target)) target_in_dict = true;

	// return case 1
	if (words.empty()) {
		result = "invalid target";
		return;
	}

	char delim = ',';
	if (target_in_dict) delim = '+';
	for (auto &w : words)
		result += w + delim;
	result = result.substr(0, result.length() - 1);
}

//
//int main() {
//	string target = "badminton";
//	unordered_set<std::string> dictionary;
//	dictionary.insert("badminton");
//	dictionary.insert("bad");
//	dictionary.insert("mint");
//	dictionary.insert("on");
//	dictionary.insert("on");
//	dictionary.insert("on");
//	string result;
//	build_string(target, dictionary, result);
//	return 0;
//}

