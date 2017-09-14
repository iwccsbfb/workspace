#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;
//#include "Problem2.h"

class Problem2 {
public:
	int getNumberOfLuckyBusTickets();
	int sub_solve(int n, int k);
};


int sub_solve0(int n, int k) {
	if (k == 1) {
		if (n >= 0 && n <= 9) {
			return 1;
		}
		return 0;
	}
	int ret = 0;
	for (int i = 0; i < 10; i++) {
		ret += sub_solve0(n - i, k-1);
	}
	return ret;
}

int Problem2::sub_solve(int n, int k) {
	vector<int> res(k*9 + 1, 0);
	for (int i = 0; i < 10; i++) {
		res[i] = 1;
	}
	for (int i = 1; i < k; i++) {
		vector<int> tmp(k * 9 + 1, res[0]);
		for (int j = 1; j < 10; j++) {
			tmp[j] = tmp[j-1] + res[j];
		}
		for (int j = 10; j < k * 9 + 1; j++) {
			tmp[j] = tmp[j - 1] + res[j] - res[j - 10];
		}
		swap(res, tmp);
	}
	return res[n];
}

//Given an array of numbers, return an integer
int Problem2::getNumberOfLuckyBusTickets()
{
	//Please Implement this
	int cnt[28];
	int ret = 0;
	for (int i = 0; i < 28; i++) {
		cnt[i] = sub_solve(i, 3);
		cout << cnt[i] << endl;
		ret += cnt[i] * cnt[i];
	}

	return ret;
}



vector < int > sortIntegers(vector < int > n) {
  vector<int> v(10, 0);
  for (auto i : n)
    v[i - 1] ++;
  int idx = 0; // the start index of number i+1
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < v[i]; j++)
      n[idx + j] = i + 1;
    idx += v[i];
  }
  return n;
}

long long power(int p, int q)
{
  // declare tmp as long long
  long long ret = 1, tmp = p;
  while (q) {
    if (q & 1)
      ret *= tmp;
    tmp *= tmp;
    q >>= 1;
  }
  return ret;
}

string sortSegments(string s) {
  string ret = s;
  if (s.length() < 2)
    return ret;
  // if it is a number
  int status = (isalpha(ret[0]) == 0);
  int start = 0, curstatus = 0;
  for (int i = 1; i < s.length(); i++) {
    curstatus = (isalpha(ret[i]) == 0);
    if (curstatus != status) {
      status = curstatus;
      sort(ret.begin() + start, ret.begin() + i);
      start = i;
    }
  }
  if (start != s.size()) {
    sort(ret.begin() + start, ret.begin() + ret.length());
  }
  return ret;
}


vector<int> shuffle(vector<int> array) {
  int n = array.size();
  vector<bool> flag(n, false);
  vector<int> res;
  while (res.size() < n) {
    int idx = rand() % n;
    if (!flag[idx]) {
      flag[idx] = true;
      res.push_back(array[idx]);
    }
  }
  return res;
}

//auto res = shuffle({ 1,2,3,4,5 });
//for (auto i : res) cout << i << ' ';

#include <unordered_map>
/*
Please note that it's Function problem i.e.
you need to write your solution in the form Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/

// [0,idx) is the common prefix
int common_prefix_idx(string &s1, string &s2) {
  int i = 0;
  for (; i<min(s1.size(), s2.size()); i++) {
    if (s1[i] != s2[i]) break;
  }
  return i;
}

/*The function should return a string denoting the
order?? of the words in the Alien Dictionary */
string printOrder(string dict[], int N, int k)
{
  unordered_map<char, int> m;
  string res; 
  for (int i = 0; i < k; i++) res += '1';

  for (int i = 0; i<k; i++) m['a' + i] = i;
  for (int i = 0; i<N - 1; i++) {
    string &s1 = dict[i], &s2 = dict[i + 1];
    int idx = common_prefix_idx(s1, s2);
    if (idx == s1.size() || idx == s2.size())
      continue;
    if (m[s1[idx]] > m[s2[idx]])
      std::swap(m[s1[idx]], m[s2[idx]]);
  }
  for (auto kv : m) {
    res[kv.second] = kv.first;
  }
  return res;
}

#include <unordered_map>
struct node {
//private:
  node * children[2];
  char ch; // if 0, it is a leaf node
//public:
  node(char c=0) : ch(c) { 
    children[0] = children[1] = nullptr; 
  }
  ~node() {
    if (children[0] != nullptr) {
      delete children[0];
      children[0] = nullptr;
    }
    if (children[1] != nullptr) {
      delete children[1];
      children[1] = nullptr;
    }
  }
  void insert_left() {
    if (children[0] == nullptr) 
      children[0] = new node();
  }

  void insert_right() {
    if (children[1] == nullptr) 
      children[1] = new node();
  }

  void set_value(char c) {
    ch = c;
  }

  bool is_leaf() {
    return children[0] == nullptr && children[1] == nullptr;
  }
};

void insert(node *n, string &s, char val) {
  for (char ch : s) {
    if(ch == '0') {
      n->insert_left();
      n = n->children[0];
    }
    else { // ch =='1'
      n->insert_right();
      n = n->children[1];
    }
  }
  n->ch = val;
}

string decode2(vector<string>codes, string encoded) {
  node * head = new node();
  for (auto code : codes) {
    char ch;
    int idx = code.find_first_of('\t');
    if (idx != 1)  ch = '\n';
    else ch = code[0];
    string s = code.substr(idx + 1);
    insert(head, s, ch);
  }
  string res;
  node * tmp = head;
  for (char ch : encoded) {
    tmp = tmp->children[ch - '0'];
    if (tmp->is_leaf()) {
      res += tmp->ch;
      tmp = head;
    }
  }
  return res;
}

string decode(vector<string>codes, string encoded) {
  unordered_map<string, int> m;
  for (auto code : codes) {
    char ch; 
    int idx = code.find_first_of('\t');
    if (idx != 1)  ch = '\n';
    else ch = code[0];
    string s = code.substr(idx + 1);
    m[s] = ch;
  }
  int start = 0, len = 1;
  string res;
  while (start + len <= encoded.size()) {
    string s = encoded.substr(start, len);
    if (m.find(s) != m.end()) {
      res += m[s];
      start += len;
      len = 0;
    }
    else len++;
  }
  return res;
}
//cout << decode2({ "a\t100100", "b\t100101", "c\t110001", "d\t100000", "[newline]\t111111", "p\t111110", "q\t000001" }, "111110000001100100");



#include <algorithm>
#include <string>
#include <unordered_set>
#include <unordered_map>
using namespace std;

bool compare(string s1, string s2) {
  return s1.size() > s2.size();
}

int getWordLength(string &word, unordered_set<string> &set, unordered_map<string, int> &cache) {
  if (word.size() <= 1) return word.size();
  if (cache.find(word) != cache.end())
    return cache[word];
  // chain length is at least 1
  int res = 1;
  for (int i = 0; i<word.size(); i++) {
    // remove the i-th letter
    string s = word.substr(0, i) + word.substr(i + 1);
    if (set.find(s) != set.end()) {
      int length = getWordLength(s, set, cache);
      res = max(res, length + 1);
    }
  }
  cache[word] = res;
  return res;
}

int longestChain(vector < string > words) {
  unordered_set<string> set;
  for (auto &word : words)
    set.insert(word);
  // sort the vector be word length, put the longest at the beginning
  sort(words.begin(), words.end(), compare);
  int res = 0;
  unordered_map<string, int> cache;
  for (auto &word : words) {
    if (word.size() <= res)
      // early exit: 
      // the chain length of a word is at most its length 
      break;
    res = max(res, getWordLength(word, set, cache));
  }
  return res;
}


// mark the friend circle of i-th person as visited
void helper_dfs(size_t i, vector<string> & friends, vector<bool> &visited) {
  visited[i] = true;
  string &s = friends[i];
  for (int j = 0; j < s.size(); j++) {
    if (s[j] == 'Y' && !visited[j])
      // if j is a unvisited friend, visit his friends
      helper_dfs(j, friends, visited);
  }
}

int friendCircles(vector < string > friends) {
  int n = friends.size();
  vector<bool> visited(n, false);
  int res = 0;
  for (int i = 0; i < n; i++) {
    if (visited[i]) continue;
    helper_dfs(i, friends, visited);
    res += 1;
  }
  return res;
}


#include <iostream>
int main() {
  //cout << longestChain({ "a","b","ba","bca","bda","bdca" }) << endl;
  cout << friendCircles({ "YYNN", "YYYN", "NYYN", "NNNY" }) << endl;
}