#include "./setup.h"

int main() {
   vector<string> grid;
   grid.emplace_back();
   while (cin >> grid.back()) grid.emplace_back();
   grid.pop_back();
   int rows = grid.size();
   int cols = grid[0].size();

   // find guard
   int gr = -1, gc = -1;
   for (int r = 0; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) {
         if (grid[r][c] != '^') continue;

         gr = r; gc = c;
      }
   }

   // simulate for each (detect cycles)
   auto checkCycle = [&]() {
      vector<vector<bitset<4>>> visited(rows, vector<bitset<4>>(cols)); // visited[r][c][d] = visited grid r, c pointing in direction d
      int r = gr;
      int c = gc;
      int dir = 0;
      visited[r][c][dir] = true;
      int offsets[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
      while (true) {
         int nr = r + offsets[dir][0], nc = c + offsets[dir][1];
         if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) break;

         if (grid[nr][nc] == '#') {
            dir = (dir + 1) & 0b11;
         } else {
            r = nr;
            c = nc;
            if (visited[r][c][dir]) return true;
            visited[r][c][dir] = true;
         }
      }
      return false;
   };
   int cycles = 0;
   for (int r = 0; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) {
         if (grid[r][c] != '.') continue;

         char t = grid[r][c];
         grid[r][c] = '#';
         cycles += checkCycle();
         grid[r][c] = t;
      }
   }
   cout << cycles << endl;
}