#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <unordered_map>
#include <map>
#include <queue>
using namespace std;

//#include "Problem5.h"
/*Given a grid, return a solution object.
*
* A solution object is a struct that contains the following.
* = amountOfTime == an int stating how much time it took to complete the maze.
* = directions == an array of Problem5::Directions that dictates the path through the maze.
* = isPossible == a boolean that says *if* there is a path through the maze.
*
* A Problem5::Direction is an enum with six states {EAST, WEST, SOUTH,
* NORTH, UP, DOWN} you can access this via Problem5::Problem5::Direction::NORTH etc.
*
* A ThreeDimCharArray is a std::vector<std::vector<std::vector>>>.
*/
using ThreeDimCharArray = std::vector<std::vector<std::vector<int>>>;


class Solution;

class Problem5 {
public:
	enum Direction {
		EAST, WEST, SOUTH, NORTH, UP, DOWN
	};
	class Solution {
	public:
		int amountOfTime;
		vector<Problem5::Direction> directions;
		bool isPossible;
	};
	Solution Problem5::savePrincess(ThreeDimCharArray grid);
};


Problem5::Direction get_dir(int nx, int ny, int nh, int x, int y, int h) {
	if (nx - x == -1) {
		return Problem5::Direction::EAST;
	}
	if (nx - x == 1) {
		return Problem5::Direction::WEST;
	}
	if (ny - y == -1) {
		return Problem5::Direction::SOUTH;
	}
	if (ny - y == 1) {
		return Problem5::Direction::NORTH;
	}

	if (nh - h == -1) {
		return Problem5::Direction::DOWN;
	}
	// No jumping up
}

int get_idx(int x, int y, int h, int X, int Y) {
	return h * X * Y + X*y + x;
}
void get_cord(int idx, int& x, int&y, int& z, int X, int Y) {
	z = idx / (X*Y);
	idx = idx % (X*Y);
	y = idx / X;
	x = idx % X;
}

vector<int> getneibor(int x, int y, int h, int X, int Y, int H, ThreeDimCharArray& grid) {
	vector<int> res;
	int newx, newy, newz;
	newx = x - 1;
	if (newx >= 0 && grid[h][y][newx] != 'o') {
		res.push_back(get_idx(newx, y, h, X, Y));
	}
	newx = x + 1;
	if (newx < X && grid[h][y][newx] != 'o') {
		res.push_back(get_idx(newx, y, h, X, Y));
	}

	newy = y - 1;
	if (newy >= 0 && grid[h][newy][x] != 'o') {
		res.push_back(get_idx(x, newy, h, X, Y));
	}
	newy = y + 1;
	if (newy < Y && grid[h][newy][x] != 'o') {
		res.push_back(get_idx(x, newy, h, X, Y));
	}
	//  cannot jump up
	//newz = h - 1;
	//if (newz >= 0 && grid[newz][y][x] != 'o') {
	//	res.push_back(getidx(x, y, newz, X, Y));
	//}
	newz = h + 1;
	if (newz < H && grid[newz][y][x] != 'o') {
		res.push_back(get_idx(x, y, newz, X, Y));
	}
	return res;
}

int get_min_idx(unordered_map<int, int>& dis_map, set<int>& vset) {
	int dis = INT_MAX;
	int ret = -1;
	for (auto& idx : vset) {
		if (dis_map[idx] < dis) {
			dis = dis_map[idx];
			ret = idx;
		}
	}
	return ret;
}



Problem5::Solution Problem5::savePrincess(ThreeDimCharArray grid)
{
	Solution sn;
	sn.amountOfTime = 0;
	sn.directions = std::vector<Problem5::Direction>();
	sn.isPossible = false;

	int H = grid.size();
	int Y = grid[0].size();
	int X = grid[0][0].size();
	int pcnt = H*Y*X;

	// using dijkstra's algo
	// initialization
	set<int> vset;
	unordered_map<int, int> dis_map;
	unordered_map<int, int> prev;
	for (int h = 0; h < H; h++) {
		for (int x = 0; x < X; x++) {
			for (int y = 0; y < Y; y++) {
				int idx = get_idx(x, y, h, X, Y);
				vset.insert(idx);
				int dist = idx == 0 ? 0 : INT_MAX;
				dis_map[idx] = dist;
				prev[idx] = -1;
			}
		}
	}
	// find the shortest path from the prince to each node
	while (vset.size()) {
		int cur_idx = get_min_idx(dis_map, vset);
		// if the pricess is unreachable, break
		if (cur_idx < 0)  break;
		int curdis = dis_map[cur_idx];
		vset.erase(cur_idx);
		int ux, uy, uh;
		get_cord(cur_idx, ux, uy, uh, X, Y);
		auto nbvec = getneibor(ux, uy, uh, X, Y, H, grid);
		for (auto& nid : nbvec) {
			int new_dist = curdis + 1;
			if (new_dist < dis_map[nid]) {
				dis_map[nid] = new_dist;
				prev[nid] = cur_idx;
			}
		}
	}
	int x = X - 1, y = Y - 1, h = H - 1;
	// find location of the princess
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			if (grid[H - 1][y][x] == '2') {
				x = i; y = j;
				break;
			}
		}
	}
	// find the path to princess
	int idx_princess = get_idx(x, y, H - 1, X, Y);
	// 
	if (dis_map[idx_princess] < INT_MAX) {
		sn.amountOfTime = 5 * dis_map[idx_princess];
		while (grid[h][y][x] != '1') {
			int cur_idx = get_idx(x, y, h, X, Y);
			int nidx = prev[cur_idx];
			int nx, ny, nh;
			get_cord(nidx, nx, ny, nh, X, Y);
			sn.directions.push_back(get_dir(nx, ny, nh, x, y, h));
			x = nx; y = ny; h = nh;
		}
		reverse(sn.directions.begin(), sn.directions.end());
		sn.isPossible = true;
	}
	return sn;
}

int main() {
	Problem5 p5;
	ThreeDimCharArray grid = {
		{
			{ '1', '.', '.' , '.' },
			{ 'o', 'o', '.', '.' },
			{ '.', '.', '.', '.' }
		},
		{
			{ 'o', 'o', 'o', '.' },
			{ '.', '.', 'o', '.' },
			{ '.', 'o', 'o', 'o' }
		},
		{
			{ 'o', 'o', 'o' , '.' },
			{ 'o', '.', 'o', 'o' },
			{ 'o', 'o', '2' , '.' }
		}
	};
	p5.savePrincess(grid);
	return 0;
}
