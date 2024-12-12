#include "./setup.h"

int main() {
  vector<string> grid(1);
  string s;
  while (cin >> s) grid.push_back("#" + s + "#");
  grid.emplace_back();
  grid.front().resize(grid[1].size(), '#');
  grid.back().resize(grid[1].size(), '#');

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

  // region 0 always the border
  // calc perimeters by checking left/up boundaries
  // each side matches a corner/bend
  for (int r = 1; r+1 < rows; ++r) {
    for (int c = 1; c+1 < cols; ++c) {
      int x = region[r][c];
      int nu = region[r-1][c];
      int nl = region[r][c-1];
      int nd = region[r+1][c];
      int nr = region[r][c+1];
      int nul = region[r-1][c-1];
      int nur = region[r-1][c+1];
      int ndl = region[r+1][c-1];
      int ndr = region[r+1][c+1];
      int &p = regionPerimeters[x];

      // corners
      p += nu != x && nl != x;
      p += nu != x && nr != x;
      p += nd != x && nl != x;
      p += nd != x && nr != x;

      // bends
      p += nu == x && nl == x && nul != x;
      p += nu == x && nr == x && nur != x;
      p += nd == x && nl == x && ndl != x;
      p += nd == x && nr == x && ndr != x;
    }
  }

  // output
  ll sum = 0;
  for (int i = 1; i < numRegions; ++i) {
    sum += (ll)regionAreas[i] * (ll)regionPerimeters[i];
  }
  cout << sum << endl;
}