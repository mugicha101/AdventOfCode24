#include "./setup.h"

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int main() {
  const int n = 71;
  const int k = 1024;
  vector<vector<bool>> visited(n, vector<bool>(n, false));
  vector<pair<int,int>> vals(1);
  while (cin >> vals.back().first, cin.ignore(1), cin >> vals.back().second) {
    vals.emplace_back();
  }
  vals.pop_back();
  for (int i = 0; i < k; ++i) {
    visited[vals[i].first][vals[i].second] = true;
  }

  queue<pair<int,int>> q;
  q.emplace(0, 0);
  visited[0][0] = true;
  int dist = 0;
  while (!visited[n-1][n-1]) {
    ++dist;
    for (int qi = q.size(); qi > 0; --qi) {
      auto [r, c] = q.front();
      q.pop();
      auto check = [&](int nr, int nc) {
        if (visited[nr][nc]) return;
        
        visited[nr][nc] = true;
        q.emplace(nr, nc);
      };
      if (r) check(r-1, c);
      if (c) check(r, c-1);
      if (r+1 < n) check(r+1, c);
      if (c+1 < n) check(r, c+1);
    }
  }
  cout << dist << endl;
}