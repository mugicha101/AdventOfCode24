#include "./setup.h"

int main() {
  vector<string> grid(1);
  while (cin >> grid.back()) grid.emplace_back();
  grid.pop_back();
  int rows = grid.size();
  int cols = grid[0].size();

  vector<vector<int>> paths(rows, vector<int>(cols));
  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      paths[r][c] = grid[r][c] == '0';
    }
  }
  for (char v = '1'; v <= '9'; ++v) {
    for (int r = 0; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) {
        if (grid[r][c] != v) continue;

        auto check = [&](int nr, int nc) {
          if (grid[nr][nc] == v-1) paths[r][c] += paths[nr][nc];
        };
        if (r) check(r-1, c);
        if (c) check(r, c-1);
        if (r+1 < rows) check(r+1, c);
        if (c+1 < cols) check(r, c+1);
      }
    }
  }
  int sum = 0;
  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      if (grid[r][c] == '9') sum += paths[r][c];
    }
  }
  cout << sum << endl;
}