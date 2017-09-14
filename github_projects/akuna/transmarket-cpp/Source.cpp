#include <iostream>
#include <string>
#include <vector> 
#include <math.h>
using namespace std;


#include <unordered_map>
#include <algorithm>
string electionWinner(vector<string> votes) {
  unordered_map<string, int> map;
  for (auto s : votes) map[s]++;
  int max_count = 0;
  for (auto kv : map) max_count = std::max(max_count, kv.second);
  vector<string> res;
  for (auto kv : map)
    if (kv.second == max_count)
      res.push_back(kv.first);
  sort(res.begin(), res.end());
  return res.back();
}


int maxStep(int n, int k) {
  // if there is an x, such that x(x+1)/2 == k
  bool flag = false;
  int x = sqrt(k);
  while (x*(x + 1) <= 2 * k) {
    if (x*(x + 1) == 2 * k)
      flag = true;
    x++;
  }
  int res = n*(n + 1) / 2;
  if (flag)
    return res - 1;
  return res;
}



#include <assert.h>
void traverse_dfs(vector<vector<int>> &maze, vector<vector<bool>> &visited, int i, int j, int &count) {
  int n = maze.size();
  visited[i][j] = true;
  if (maze[i][j] > 1) count++;
  if (i - 1 >= 0 && maze[i - 1][j] != 1 && !visited[i - 1][j])
    traverse_dfs(maze, visited, i - 1, j, count);
  if (j - 1 >= 0 && maze[i][j - 1] != 1 && !visited[i][j - 1])
    traverse_dfs(maze, visited, i, j - 1, count);
  if (i + 1 < n && maze[i + 1][j] != 1 && !visited[i + 1][j])
    traverse_dfs(maze, visited, i + 1, j, count);
  if (j + 1 < n && maze[i][j + 1] != 1 && !visited[i][j + 1])
    traverse_dfs(maze, visited, i, j + 1, count);
}

int get_dist(vector<vector<int>> &dist, int i, int j) {
  return dist[min(i, j)][max(i, j)];
}

void set_dist(vector<vector<int>> &dist, int i, int j, int val) {
  dist[i][j] = dist[j][i] = val;
}

bool is_block(vector<vector<int>> &maze, int idx) {
  int n = maze.size();
  return maze[idx / n][idx % n] == 1;
}

int helper_cheese(vector<int> cheese_idx, int start_cheese,
  vector<vector<int>>  & cheese_dist, vector<int> &jerry_dist) {
  if (cheese_idx.empty())
    return jerry_dist[start_cheese];

  int result = INT_MAX;
  for (auto idx : cheese_idx) {
    int tmp = cheese_dist[start_cheese][idx];
    vector<int> new_cheese_idx;
    for (auto tmp : cheese_idx)
      if (tmp != idx) new_cheese_idx.push_back(cheese_idx[tmp]);

    int start_cheese = idx;
    tmp += helper_cheese(new_cheese_idx, idx, cheese_dist, jerry_dist);
    result = min(result, tmp);
  }
  return result;
}

int minMoves(vector<vector<int>> maze, int x, int y) {
  int n = maze.size();
  maze[x][y] = 3;

  int target_count = 0;

  vector<int> cheese_idx;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      if (maze[i][j] == 2) cheese_idx.push_back(i*n + j);
      if (maze[i][j] > 1) target_count++;
    }
  // 1st step: find if all nodes are in one connected component
  // if not, return -1
  vector<vector<bool>> visited(n, vector<bool>(n, false));
  int count = 0;
  traverse_dfs(maze, visited, 0, 0, count);
  if (count != target_count) return -1;

  // 2nd step: find distance between all pairs, using floyd algorithm
  // can also use dfs/bfs to get all distance pairs
  int size = n*n; // count of nodes
  // dont use INT_MAX, cuz when INT_MAX is plused by INT_MAX, it will overflow
  vector<vector<int>> dist(size, vector<int>(size, USHRT_MAX));
  for (int i = 0; i < size; i++) dist[i][i] = 0;
  for (int i = 0; i < size; i++) {
    // only goes to right and down direction
    if (i + n < size && !is_block(maze, i + n) && !is_block(maze, i)) 
      set_dist(dist, i, i + n, 1);
    if ((i + 1) % n != 0 && !is_block(maze, i + 1) && !is_block(maze, i))
      set_dist(dist, i + 1, i, 1);
    //if (i - n >= 0 && !is_block(maze, i - n))  set_dist(dist, i, i - n, 1);
    //if (i % n != 0 && !is_block(maze, i - 1))  set_dist(dist, i - 1, i, 1);
  }
  for (int k = 0; k < size; k++)
    for (int i = 0; i < size; i++)
      for (int j = 0; j < size; j++)
        if (dist[j][i] > get_dist(dist, i, k) + get_dist(dist, j, k))
          dist[j][i] = get_dist(dist, i, k) + get_dist(dist, j, k);
  vector<vector<int>> cheese_dist;
  vector<int> tom_dist;
  vector<int> jerry_dist;

  int tom_idx = 0, jerry_idx = x*n + y;
  for (auto idx : cheese_idx) {
    tom_dist.push_back(get_dist(dist, tom_idx, idx));
    jerry_dist.push_back(get_dist(dist, jerry_idx, idx));

    vector<int> tmp;
    for (auto idx2 : cheese_idx)
      tmp.push_back(get_dist(dist, idx, idx2));
    cheese_dist.push_back(tmp);
  }

  // 3rd step: traverse all k! possible paths
  assert(tom_dist.size() == jerry_dist.size() && tom_dist.size() == cheese_idx.size());
  cheese_idx.clear();
  for (int i = 0; i < target_count - 1; i++) cheese_idx.push_back(i);
  int result = INT_MAX;
  for (int i = 0; i < tom_dist.size(); i++) {
    int tmp = tom_dist[i];
    vector<int> new_cheese_idx;
    for (int tmp = 0; tmp < cheese_idx.size(); tmp++)
      if (tmp != i) new_cheese_idx.push_back(tmp);
    int start_cheese = i;
    tmp += helper_cheese(new_cheese_idx, start_cheese, cheese_dist, jerry_dist);
    result = min(result, tmp);
  }
  return result;
}



bool is_prime_num(int num, vector<int> &p_nums) {
  int tmp = sqrt(num);
  // if any prime number is a factor of num, it is not prime 
  for (auto p : p_nums) {
    if (p > tmp) return true;
    if (num % p == 0)
      return false;
  }
}

vector<int> get_prime_num(int n) {
  vector<int> res;
  if (n < 2) return res;
  res.push_back(2);
  for (int i = 3; i <= n; i++) {
    if (is_prime_num(i, res))
      res.push_back(i);
  }
  return res;
}

int main() {
  float a = (float)1;
  float b = (float) 1e-10;
  cout << a << ' ' << b << endl;
  //vector<vector<int>> maze = {
  //  { 0, 2, 0 },
  //  { 0, 0, 1 },
  //  { 1, 1, 1 }
  //};
  //cout << minMoves(maze, 1, 1);

  //vector<vector<int>> maze = {
  //  {0, 1, 0},
  //  { 1, 0, 1 },
  //  {  0, 2, 2 }
  //};
  //cout << minMoves(maze, 1, 1);

  vector<vector<int>> maze = {
    { 0, 2, 0},
    { 1, 1, 2},
    { 1, 0, 0 }
  };
   cout << minMoves(maze, 2, 1);

  return 0;
}
