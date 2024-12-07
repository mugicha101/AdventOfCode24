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
         goto found;
      }
   }
   found:

   // simulate
   int dir = 0;
   grid[gr][gc] = 'X';
   int offsets[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
   while (true) {
      int ngr = gr + offsets[dir][0], ngc = gc + offsets[dir][1];
      if (ngr < 0 || ngr >= rows || ngc < 0 || ngc >= cols) break;

      if (grid[ngr][ngc] == '#') {
         dir = (dir + 1) & 0b11;
      } else {
         gr = ngr;
         gc = ngc;
         grid[gr][gc] = 'X';
      }
   }

   // count visited
   int visited = 0;
   for (int r = 0; r < rows; ++r) {
      cout << grid[r] << endl;
      for (int c = 0; c < cols; ++c) {
         visited += grid[r][c] == 'X';
      }
   }
   cout << visited << endl;
}