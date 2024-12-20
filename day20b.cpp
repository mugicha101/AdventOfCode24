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
  vector<pair<int,int>> route(1, start);
  for (int i = 0; i < (int)route.size(); ++i) {
    auto [r, c] = route[i];
    grid[r][c] = '#';
    if (grid[r-1][c] != '#') route.emplace_back(r-1, c);
    else if (grid[r][c-1] != '#') route.emplace_back(r, c-1);
    else if (grid[r+1][c] != '#') route.emplace_back(r+1, c);
    else if (grid[r][c+1] != '#') route.emplace_back(r, c+1);
  }

  // for each pair of points on the path, determine if a 20 distance cheat exists that saves 100 picoseconds or more
  int count = 0;
  for (int i = 0; i < (int)route.size(); ++i) {
    for (int j = i+1; j < (int)route.size(); ++j) {
      int dist = abs(route[j].first - route[i].first) + abs(route[j].second - route[i].second);
      int timeSave = j - i - dist;
      count += dist <= 20 && timeSave >= 100;
    }
  }
  cout << count << endl;
}