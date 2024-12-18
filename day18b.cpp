#include "./setup.h"

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

struct UnionFind {
  vector<int> uf;
  vector<int> rank;
  UnionFind(int n) : uf(n), rank(n) {
    iota(all(uf), 0);
  }

  int find(int a) {
    if (uf[a] != a) uf[a] = find(uf[a]);
    return uf[a];
  }

  bool merge(int a, int b) {
    int ra = find(a);
    int rb = find(b);
    if (ra == rb) return false;

    if (rank[ra] >= rank[rb]) {
      uf[rb] = ra;
      rank[ra] += rank[ra] == rank[rb];
    } else {
      uf[ra] = rb;
    }
    return true;
  }
};

int main() {
  const int n = 71;
  vector<pair<int,int>> vals(1);
  while (cin >> vals.back().first, cin.ignore(1), cin >> vals.back().second) {
    vals.emplace_back();
  }
  vals.pop_back();

  vector<vector<int>> drops(n, vector<int>(n, false));
  for (auto [r, c] : vals) ++drops[r][c];

  UnionFind uf(n * n);
  for (int r = 0; r < n; ++r) {
    for (int c = 0; c < n; ++c) {
      if (drops[r][c]) continue;

      auto check = [&](int nr, int nc) {
        if (drops[nr][nc]) return;

        uf.merge(r * n + c, nr * n + nc);
      };
      if (r) check(r-1, c);
      if (c) check(r, c-1);
      if (r+1 < n) check(r+1, c);
      if (c+1 < n) check(r, c+1);
    }
  }

  int t = (int)vals.size();
  while (uf.find(0) != uf.find(n * n - 1)) {
    auto [r, c] = vals[--t];
    if (--drops[r][c]) continue;

    auto check = [&](int nr, int nc) {
      if (drops[nr][nc]) return;

      uf.merge(r * n + c, nr * n + nc);
    };
    if (r) check(r-1, c);
    if (c) check(r, c-1);
    if (r+1 < n) check(r+1, c);
    if (c+1 < n) check(r, c+1);
  }
  cout << vals[t].first << "," << vals[t].second << endl;
}