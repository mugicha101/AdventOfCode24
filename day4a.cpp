#include "./setup.h"

int main() {
   vector<string> grid(1);
   while (cin >> grid.back()) grid.emplace_back();
   grid.pop_back();

   int rows = (int)grid.size();
   int cols = (int)grid[0].size();
   
   int sum = 0;
   vector<vector<int>> seen(rows, vector<int>(cols));
   for (int sr = 0; sr < rows; ++sr) {
      for (int sc = 0; sc < cols; ++sc) {
         if (grid[sr][sc] != 'X') continue;

         int offsets[8][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}, {-1,-1}, {-1,1}, {1,-1}, {1,1}};
         for (int o = 0; o < 8; ++o) {
            int dr = offsets[o][0];
            int dc = offsets[o][1];
            int r = sr + dr;
            int c = sc + dc;
            auto accept = [&](char l) {
               bool res = r >= 0 && r < rows && c >= 0 && c < cols && grid[r][c] == l;
               r += dr;
               c += dc;
               return res;
            };
            sum += accept('M') && accept('A') && accept('S');
         }
      }
   }

   cout << sum << endl;
}