#include "./setup.h"

int main() {
  vector<string> grid(1);
  while (cin >> grid.back()) grid.emplace_back();
  grid.pop_back();

  // get regions
  int rows = grid.size();
  int cols = grid[0].size();
  int numRegions = 0;
  vector<vector<int>> region(rows, vector<int>(cols, -1));
  vector<int> regionAreas;
  vector<int> regionPerimeters;
  auto fillRegion = [&](int sr, int sc) {
    if (region[sr][sc] != -1) return;

    int id = numRegions++;
    regionAreas.push_back(0);
    regionPerimeters.push_back(0);
    char v = grid[sr][sc];
    queue<pair<int,int>> q;
    region[sr][sc] = id;
    q.emplace(sr, sc);

    while (!q.empty()) {
      auto [r, c] = q.front();
      ++regionAreas.back();
      q.pop();
      auto check = [&](int nr, int nc) {
        if (region[nr][nc] != -1 || grid[nr][nc] != v) return;

        region[nr][nc] = id;
        q.emplace(nr, nc);
      };
      if (r) check(r-1, c);
      if (c) check(r, c-1);
      if (r+1 < rows) check(r+1, c);
      if (c+1 < cols) check(r, c+1);
    }
  };

  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      fillRegion(r, c);
    }
  }

  // calc perimeters by checking left/up boundaries
  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      int x = region[r][c];
      int u = r == 0 ? x : region[r-1][c];
      int l = c == 0 ? x : region[r][c-1];
      if (u != x) {
        ++regionPerimeters[x];
        ++regionPerimeters[u];
      }
      if (l != x) {
        ++regionPerimeters[x];
        ++regionPerimeters[l];
      }
    }
  }

  // handle borders
  for (int r = 0; r < rows; ++r) {
    ++regionPerimeters[region[r][0]];
    ++regionPerimeters[region[r][cols-1]];
  }
  for (int c = 0; c < cols; ++c) {
    ++regionPerimeters[region[0][c]];
    ++regionPerimeters[region[rows-1][c]];
  }

  // output
  ll sum = 0;
  for (int i = 0; i < numRegions; ++i) {
    sum += (ll)regionAreas[i] * (ll)regionPerimeters[i];
  }
  cout << sum << endl;
}