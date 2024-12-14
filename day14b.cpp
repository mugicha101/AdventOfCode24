#include "./setup.h"

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// const int COLS = 11, ROWS = 7;
const int COLS = 101, ROWS = 103;

struct Robot {
  ll r, c, vr, vc;

  pair<int,int> pos(int t) {
    return { ((r + vr * t) % ROWS + ROWS) % ROWS, ((c + vc * t) % COLS + COLS) % COLS };
  }
};

int main() {
  // input
  vector<Robot> robots;
  while (true) {
    char _; if (!(cin >> _)) break;
    robots.emplace_back();
    Robot &bot = robots.back();
    cin >> _ >> bot.c >> _ >> bot.r >> _ >> _ >> bot.vc >> _ >> bot.vr;
  }

  // display boards with unusually high clusters
  int t = 0;
  while (true) {
    ++t;
    vector<string> board(ROWS, string(COLS, '.'));
    for (Robot &bot : robots) {
      auto [r, c] = bot.pos(t);
      board[r][c] = '#';
    }
    int surrounded = 0;
    for (int r = 1; r+1 < ROWS; ++r) {
      for (int c = 1; c+1 < COLS; ++c) {
        surrounded += board[r-1][c] == '#' && board[r][c-1] == '#' && board[r+1][c] == '#' && board[r][c+1] == '#';
      }
    }
    if (surrounded < 20) continue;

    cout << t << "\n";
    for (string s : board) {
      cout << s << "\n";
    }
    break;
  }
}