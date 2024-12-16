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

  // setup
  vector<vector<vector<int>>> minDist(rows, vector<vector<int>>(cols, vector<int>(4, INT_MAX)));
  auto encodePos = [&](int r, int c, int dir) {
    return (r << 18) | (c << 2) | dir;
  };
  auto decodePos = [&](int pos) {
    return make_tuple(pos >> 18, (pos >> 2) & 0xffff, pos & 0b11);
  };

  // find start and end location
  pair<int,int> start;
  pair<int,int> end;
  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      if (grid[r][c] == '#') minDist[r][c][0] = minDist[r][c][1] = minDist[r][c][2] = minDist[r][c][3] = 0;
      else if (grid[r][c] == 'S') start = make_pair(r, c);
      else if (grid[r][c] == 'E') end = make_pair(r, c);
    }
  }

  // dijkstras
  priority_queue<pair<int,int>> pq;
  minDist[start.first][start.second][0] = 0;
  pq.emplace(0, encodePos(start.first, start.second, 0));
  while (!pq.empty()) {
    auto [dist, pos] = pq.top();
    auto [r, c, d] = decodePos(pos);
    pq.pop();
    if (dist != minDist[r][c][d]) continue;

    auto check = [&](int nr, int nc, int nd, int newDist) {
      if (minDist[nr][nc][nd] <= newDist) return;

      minDist[nr][nc][nd] = newDist;
      pq.emplace(newDist, encodePos(nr, nc, nd));
    };
    check(r, c, (d + 1) & 0b11, dist + 1000);
    check(r, c, (d + 2) & 0b11, dist + 2000);
    check(r, c, (d + 3) & 0b11, dist + 1000);
    switch (d) {
      case 0: check(r, c+1, d, dist + 1); break;
      case 1: check(r+1, c, d, dist + 1); break;
      case 2: check(r, c-1, d, dist + 1); break;
      case 3: check(r-1, c, d, dist + 1); break;
    }
  }
  vector<int> &endDist = minDist[end.first][end.second];
  int res = min({endDist[0], endDist[1], endDist[2], endDist[3]});
  cout << res << endl;
}