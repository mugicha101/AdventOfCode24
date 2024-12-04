#include "./setup.h"

int main() {
   vector<string> grid(1);
   while (cin >> grid.back()) grid.emplace_back();
   grid.pop_back();

   int rows = (int)grid.size();
   int cols = (int)grid[0].size();
   
   int sum = 0;
   vector<vector<int>> seen(rows, vector<int>(cols));
   for (int r = 1; r+1 < rows; ++r) {
      for (int c = 1; c+1 < cols; ++c) {
         sum += grid[r][c] == 'A'
            && ((grid[r-1][c-1] == 'S' && grid[r+1][c+1] == 'M') || (grid[r-1][c-1] == 'M' && grid[r+1][c+1] == 'S'))
            && ((grid[r-1][c+1] == 'S' && grid[r+1][c-1] == 'M') || (grid[r-1][c+1] == 'M' && grid[r+1][c-1] == 'S'));
      }
   }

   cout << sum << endl;
}