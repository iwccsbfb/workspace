#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;


// using dfs to traverse the connected component of the i-th friend
void helper(vector<string> &friends, int i, vector<bool> &visited) {
  if (visited[i]) return;
  visited[i] = true;
  auto tmp = friends[i];
  for (int j = 0; j < tmp.size(); j++) {
    // visit the j-th person's friend if he is a friend
    if (tmp[j] == 'Y')
      helper(friends, j, visited);
  }
}

int friendCircles(vector<string> friends) {
  int n = friends.size();
  vector<bool> visited(n, false);
  int count = 0;
  for (int i = 0; i < n; i++) {
    if (visited[i]) continue;
    // visit the connected component for the i-th person
    helper(friends, i, visited);
    count++;
  }
  return count;
}



#include <algorithm>
#include <unordered_set>


int get_length(string &word, unordered_set<string> &word_set, 
  unordered_map<string, int> &result_saver) {
  if (word.size() == 1) return 1;
  if (result_saver.find(word) != result_saver.end())
    return result_saver[word];
  int result = 1;
  for (int i = 0; i < word.size(); i++) {
    string new_word = word.substr(0, i) + word.substr(i+1);
    if (word_set.find(new_word) != word_set.end())
      result = max(result, 1 + get_length(new_word, word_set, result_saver));
  }
  result_saver[word] = result;
  return result;
}

int longestChain(vector<string> words) {
  sort(words.begin(), words.end(), [] (string &a, string &b) { 
    return a.size() > b.size(); 
  });
  unordered_set<string> word_set(words.begin(), words.end());
  int result = 0;
  unordered_map<string, int> result_saver;
  for (auto &word : words) {
    // early exit
    if (word.size() <= result) break;
    result = max(result, get_length(word, word_set, result_saver));
  }
  return result;
}


int main() {
  string s = "abcd";
  string s2 = s.substr(4);
  vector<string> words = { "a", "b", "ba", "bca", "bda", "bdca" };
  longestChain(words);
  return 0;
}
