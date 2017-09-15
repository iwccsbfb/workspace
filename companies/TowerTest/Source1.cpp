#include <iostream>
#include <vector>
#include <deque>
#include <unordered_set>
#include <string>
#include <algorithm>
using namespace std;

namespace arthur2 {

class Trie {
	bool end_of_word = false;
	Trie * children[256];

	// Make sure accesses are made with unsigned char
	Trie * &child_ptr(unsigned char c) {
		return children[c];
	}
public:
	Trie(const Trie &other) = delete;
	Trie &operator =(const Trie &other) = delete;

	bool contains(const char *str);

	bool contains(const std::string &s) {
		return contains(s.c_str());
	}

	void insert(const char *str);
	void insert(const std::string &s) {
		insert(s.c_str());
	}

	Trie();
	~Trie();
};

// Please implement these methods
Trie::Trie() {
	for (int i = 0; i < 256; i++) {
		children[i] = NULL;
	}
}

bool Trie::contains(const char *str) {
	Trie *p = this;
	for (int i = 0; i < strlen(str); i++) {
		if (p == NULL) return false;
		int idx = (unsigned char)(str[i]);
		p = p->children[idx];
	}
	if (p == NULL || p->end_of_word == false) return false;
	return true;
}

void Trie::insert(const char *str) {
	Trie *p = this;
	for (int i = 0; i < strlen(str); i++) {
		int idx = (unsigned char)(str[i]);
		if (p->children[idx] == NULL) {
			p->children[idx] = new Trie();
		}
		p = p->children[idx];
	}
	p->end_of_word = true;
}

Trie::~Trie() {
	for (int i = 0; i < 256; i++) {
		if (children[i] != NULL) 
			delete children[i];
	}
}


}

int count_occurrences(const std::string &str, string pattern) {
	int i, j, size1 = str.length(), size2 = pattern.length();
	if (size2 == 0)  return 0;
	int count = 0;
	for (i = 0; i <= size1 - size2; i++) {
		for (j = 0; j < size2; j++)
			if (str[i + j] != pattern[j]) break;

		if (j == size2)  count += 1;
	}
	return count;
}

void parse_string(const std::string& input, std::vector<std::string> &result) {
	int size = input.size();
	bool in_quote = false;
	int start = 0;
	for (int i = 0; i < size; i++) {
		if (input[i] == '"') 
			in_quote = !in_quote;
		if (!in_quote) {
			if (input[i] == ',') {
				std::string sub = input.substr(start, i - start);
				result.push_back(sub);
				start = i + 1;
			}
		}
	}
	if (!in_quote) {
		std::string sub = input.substr(start);
		result.push_back(sub);
	}
}


class Solution {
public:
  bool validTree(int n, vector<pair<int, int>>& edges) {
    if (n == 0) return true;
    vector< vector<int>> G(n); // use adjacency lists
    for (auto &p : edges) {
      G[p.first].push_back(p.second);
      G[p.second].push_back(p.first);
    }
    vector<bool> acc(n, false);
    vector<int> v1{ 0 }, v2;
    while (!v1.empty()) {
      for (auto i : v1) {
        for (auto j : G[i])
        {
          if (j == i) continue;
          if (acc[j])
            return false;
          acc[j] = true;
          v2.push_back(j);
        }
      }
      v1 = std::move(v2);
    }
    for (auto i : acc)
      if (!i) return false;
    return true;
  }

  //在这个写法里，path不包含cur node; 
  bool validTree2(int n, vector<pair<int, int>>& edges) {
    if (n == 0) return true;
    vector< vector<int>> G(n); // use adjacency lists
    for (auto &p : edges) {
      G[p.first].push_back(p.second);
      G[p.second].push_back(p.first);
    }
    vector<bool>acc(n, false); // accessed or not
    acc[0] = true;
    vector<int> path = {};
    if (!dfs(G, 0, path, acc)) return false;
    for (auto i : acc)
      if (!i) return false;
    return true;
  }

private:
  bool dfs(vector<vector<int>> &G, int cur, vector<int> &path, vector<bool> &acc) {
    acc[cur] = true;
    for (auto &nb : G[cur]) {
      if (!path.empty() && nb == path.back()) continue;
      if (exist(path, nb)) return false;

      path.push_back(cur);
      if (!dfs(G, nb, path, acc)) return false;
      path.pop_back();
    }
    return true;
  }
  inline bool exist(vector<int> &v, int ele) {
    for (auto &i : v) if (i == ele) return true;
    return false;
  }
};


int main() {
  sortIntegers({ 1,2,3,4,5,1 });
  //int ** a; 
  //auto b = const_cast<const int **> (a);
	//string input = ",this,is,\"a,test\", \"a,bc\",,";
	//vector<string> result;
	//parse_string(input, result);
	return 0;
}