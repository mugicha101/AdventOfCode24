#include "./setup.h"

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int main() {
  // grid input
  vector<string> grid;
  string s;
  while (getline(cin, s), s.size()) {
    grid.push_back(s);
  }
  int rows = grid.size();
  int cols = grid[0].size();

  // find starting location
  int sr = 0, sc = 0;
  for (sr = 0; sr < rows; ++sr) {
    for (sc = 0; sc < cols && grid[sr][sc] != '@'; ++sc);
    if (grid[sr][sc] == '@') break;
  }
  if (sr == rows) {
    cerr << "START NOT FOUND" << endl;
    exit(-1);
  }
  grid[sr][sc] = '.';

  auto inBounds = [&](int r, int c) { return r >= 0 && c >= 0 && r < rows && c < cols; };

  auto handleMove = [&](char move) {
    int dr, dc;
    switch (move) {
      case '<': {
        dr = 0;
        dc = -1;
      } break;
      case '>': {
        dr = 0;
        dc = 1;
      } break;
      case '^': {
        dr = -1;
        dc = 0;
      } break;
      case 'v': {
        dr = 1;
        dc = 0;
      } break;
      default: {
        cerr << "INVALID MOVE " << move << endl;
        exit(-1);
      }
    }

    // handle wall 
    if (!inBounds(sr+dr, sc+dc) || grid[sr+dr][sc+dc] == '#') return;

    // handle box
    if (grid[sr+dr][sc+dc] == 'O') {
      int r = sr+dr+dr, c = sc+dc+dc;
      while (inBounds(r, c) && grid[r][c] == 'O') {
        r += dr;
        c += dc;
      }
      if (!inBounds(r, c) || grid[r][c] == '#') return;
      grid[r][c] = 'O';
      grid[sr+dr][sc+dc] = '.';
    }

    // move robot
    sr = sr + dr;
    sc = sc + dc;
  };

  // move sequence
  while (cin >> s) {
    for (char c : s) {
      handleMove(c);
    }
  }

  // sum up positions
  int sum = 0;
  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      if (grid[r][c] != 'O') continue;

      sum += r * 100 + c;
    }
  }
  cout << sum << endl;
}