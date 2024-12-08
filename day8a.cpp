#include "./setup.h"

int main() {
   vector<string> grid(1);
   while (cin >> grid.back()) grid.emplace_back();
   grid.pop_back();

   int rows = grid.size();
   int cols = grid[0].size();

   // find all towers (grouped by char)
   unordered_map<char,vector<pair<int,int>>> towers;
   for (int r = 0; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) {
         if (grid[r][c] != '.') towers[grid[r][c]].emplace_back(r, c);
      }
   }

   // for each pos, check all pairs of towers
   auto checkPos = [&](int r, int c) {
      for (auto &[_, group] : towers) {
         int n = group.size();
         for (int i = 0; i < n; ++i) {
            pair<int,int> v1 = make_pair(group[i].first - r, group[i].second - c);
            if (v1.first == 0 && v1.second == 0) continue;

            for (int j = i+1; j < n; ++j) {
               pair<int,int> v2 = make_pair(group[j].first - r, group[j].second - c);
               if (v2.first == 0 && v2.second == 0) continue;

               auto norm = [](pair<int,int> v) {
                  if (v.first < 0) {
                     v.first = -v.first;
                     v.second = -v.second;
                  }
                  int d = v.first == 0 ? abs(v.second) : v.second == 0 ? abs(v.first) : gcd(v.first, abs(v.second));
                  v.first /= d;
                  v.second /= d;
                  return make_pair(v, d);
               };
               auto [n1, m1] = norm(v1);
               auto [n2, m2] = norm(v2);
               if (n1 != n2) continue;

               if (min(m1, m2) * 2 == max(m1, m2)) return true;
            }
         }
      }
      return false;
   };
   int antinodes = 0;
   for (int r = 0; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) {
         antinodes += checkPos(r, c);
      }
   }
   cout << antinodes << endl;
}