/*
 * GameOfLife.cpp
 *
 *  Created on: Dec 18, 2016
 *      Author: Zengye
 */
#include "header.h"


// - game of life 1D
void gameOfLife1D(vector<int> &board) {
    int n = board.size();

    for (int i = 0; i < board.size(); ++ i) {
        int liveCount = (board[(i + n - 1) % n] & 1) + (board[(i + n + 1) % n] & 1);
        if (liveCount == 1) { // change status
            if (board[i] & 1) board[i] = 1; // 0 <- 1
            else board[i] = 2;              // 1 <- 0
        } else {
            if (board[i] & 1) board[i] = 3; // 1 <- 1
            else board[i] = 0;              // 0 <- 0
        }
    }

    for (int i = 0; i < board.size(); ++ i)
        board[i] >>= 1; // right shift 1 to get only new status
}


// - game of life 2D
// follow up: https://segmentfault.com/a/1190000003819277
void gameOfLife2D(vector<vector<int> > &board) {
    int n = board.size();
    for (int i = 0; i < n; ++ i) {
        int m = board[0].size();
        for (int j = 0; j < m; ++ j) {
            int liveCount = 0;
            // search neighbors
            for (int x = max(i - 1, 0); x <= min(i + 1, n-1); ++ x) {
                for (int y = max(j - 1, 0); y <= min(j + 1, m-1); ++ y) {
                    if (x == i && y == j)
                        continue;
                    if (board[x][y] & 1)
                        liveCount ++;
                }
            }
            // if need to search neighbors with rotate matrix: use mod
            /*
              // search neighbors
              for (int x = i + n -1; x <= i + n + 1; ++ x) {
                for (int y = j + m - 1; y <= j + m + 1; ++ y) {
                  if (x % n == i && y % m == j) // self, skip
                    continue;
                  if (board[x % n][y % m] & 1)
                    liveCount ++;
                }
              }
             */

            if (board[i][j] & 1) { // current is live (i.e. lower bit is 1)
                if (liveCount == 2 || liveCount == 3)
                    board[i][j] = 3; // 1 <- 1
                else
                    board[i][j] = 1; // 0 <- 1
            } else { // current is dead
                if (liveCount == 3)
                    board[i][j] = 2; // 1 <- 0
                else
                    board[i][j] = 0; // 0 <- 0
            }
        }
    }

    for (int i = 0; i < board.size(); ++ i) {
        for (int j = 0; j < board[0].size(); ++ j) {
            board[i][j] >>= 1; // right shift 1 to get only new status
        }
    }
}

