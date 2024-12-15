#include "./setup.h"

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int main() {
  // grid input
  vector<string> grid;
  string s;
  while (getline(cin, s), s.size()) {
    grid.push_back(s);
  }
  int rows = grid.size();
  int cols = grid[0].size();

  // convert grid to sparse map of walls and obstacles
  map<pair<int,int>,char> objects; // uses left-side position
  int sr = -1, sc = -1;
  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      switch (grid[r][c]) {
        case '.': break;
        case 'O': case '#': {
          objects[make_pair(r, c * 2)] = grid[r][c];
        } break;
        case '@': {
          sr = r; sc = c * 2;
        } break;
        default: {
          cerr << "UNKNOWN TILE " << grid[r][c] << endl;
          exit(-1);
        }
      }
    }
  }
  if (sr == -1) {
    cerr << "START NOT FOUND" << endl;
    exit(-1);
  }
  auto display = [&]() {
    for (int r = 0; r < rows; ++r) {
      for (int c = 0; c < cols * 2; ++c) {
        auto obj = sr == r && sc == c ? '@' : objects.contains({r, c}) ? objects[{r, c}] == 'O' ? '[' : '#' : objects.contains({r, c-1}) ? objects[{r, c-1}] == 'O' ? ']' : '#' : '.';
        cout << obj;
      }
      cout << "\n";
    }
  };
  auto handleMove = [&](char move) {
    int dr, dc;
    switch (move) {
      case '<': {
        dr = 0;
        dc = -1;
      } break;
      case '>': {
        dr = 0;
        dc = 1;
      } break;
      case '^': {
        dr = -1;
        dc = 0;
      } break;
      case 'v': {
        dr = 1;
        dc = 0;
      } break;
      default: {
        cerr << "INVALID MOVE " << move << endl;
        exit(-1);
      }
    }

    // get object chain
    vector<tuple<int,int,char>> objChain;
    bool wall = false;
    auto checkPos = [&](int r, int c) {
      if (!objects.contains({r,c})) return;
      
      char t = objects[{r, c}];
      objects.erase({r, c});
      wall |= t == '#';
      objChain.emplace_back(r, c, t);
    };
    checkPos(sr+dr, sc+dc-1);
    checkPos(sr+dr, sc+dc);
    for (int i = 0; !wall && i < (int)objChain.size(); ++i) {
      auto [r, c, t] = objChain[i];
      checkPos(r+dr, c+dc-1);
      checkPos(r+dr, c+dc);
      checkPos(r+dr, c+dc+1);
    }
    if (wall) {
      // replace objects
      for (auto [r, c, t] : objChain) {
        objects[{r, c}] = t;
      }
      return;
    }

    // move objects
    sr += dr;
    sc += dc;
    for (auto [r, c, t] : objChain) {
      objects[{r+dr, c+dc}] = 'O';
    }
  };

  // move sequence
  while (cin >> s) {
    for (char c : s) {
      handleMove(c);
    }
  }

  // sum up positions
  int sum = 0;
  for (auto &[pos, type] : objects) {
    if (type != 'O') continue;

    sum += pos.first * 100 + pos.second;
  }
  display();
  cout << sum << endl;
}