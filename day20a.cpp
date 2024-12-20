#include "./setup.h"

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int main() {
  vector<string> grid(1);
  while (cin >> grid.back()) grid.emplace_back();
  grid.pop_back();
  int rows = grid.size();
  int cols = grid[0].size();

  // find start
  pair<int,int> start;
  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      if (grid[r][c] == 'S') {
        start = {r, c};
      }
    }
  }

  // only one route so construct it
  vector<vector<int>> time(rows, vector<int>(cols, -1));
  vector<pair<int,int>> route(1, start);
  for (int i = 0; i < (int)route.size(); ++i) {
    auto [r, c] = route[i];
    grid[r][c] = '#';
    time[r][c] = i;
    if (grid[r-1][c] != '#') route.emplace_back(r-1, c);
    else if (grid[r][c-1] != '#') route.emplace_back(r, c-1);
    else if (grid[r+1][c] != '#') route.emplace_back(r+1, c);
    else if (grid[r][c+1] != '#') route.emplace_back(r, c+1);
  }

  // check shortcuts by checking walls touching at least 2 points on the route
  int count = 0;
  for (int r = 1; r+1 < rows; ++r) {
    for (int c = 1; c+1 < cols; ++c) {
      if (time[r][c] != -1) continue;

      auto check = [&](int sr, int sc, int dr, int dc) {
        count += time[sr][sc] != -1 && time[dr][dc] != -1 && time[dr][dc] - time[sr][sc] - 2 >= 100;
      };

      check(r-1, c, r+1, c);
      check(r-1, c, r, c-1);
      check(r-1, c, r, c+1);

      check(r+1, c, r-1, c);
      check(r+1, c, r, c-1);
      check(r+1, c, r, c+1);

      check(r, c-1, r, c+1);
      check(r, c-1, r-1, c);
      check(r, c-1, r+1, c);

      check(r, c+1, r, c-1);
      check(r, c+1, r-1, c);
      check(r, c+1, r+1, c);
    }
  }
  cout << count << endl;
}