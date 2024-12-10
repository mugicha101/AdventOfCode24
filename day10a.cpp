#include "./setup.h"

int main() {
  vector<string> grid(1);
  while (cin >> grid.back()) grid.emplace_back();
  grid.pop_back();
  int rows = grid.size();
  int cols = grid[0].size();

  vector<pair<int,int>> q;
  auto qPush = [&](int r, int c) {
    grid[r][c] = grid[r][c] + 16;
    q.emplace_back(r, c);
  };
  auto qClear = [&]() {
    for (auto &[r, c] : q)
      grid[r][c] = grid[r][c] - 16;
    q.clear();
  };

  int sum = 0;

  // find unique reachable 9s from trailhead (sr, sc)
  auto findReachable = [&](int sr, int sc) {
    qPush(sr, sc);
    int res = 0;
    for (int i = 0; i < (int)q.size(); ++i) {
      auto [r, c] = q[i];
      char v = grid[r][c] - 16;
      if (v == '9') {
        ++res;
        continue;
      }
      auto check = [&](int nr, int nc) {
        if (grid[nr][nc] == v+1) qPush(nr, nc);
      };
      if (r) check(r-1, c);
      if (c) check(r, c-1);
      if (r+1 < rows) check(r+1, c);
      if (c+1 < cols) check(r, c+1);
    }
    qClear();
    return res;
  };
  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      if (grid[r][c] != '0') continue;

      sum += findReachable(r, c);
    }
  }
  cout << sum << endl;
}