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

  // sim
  ll quads[4] = {};
  for (Robot &bot : robots) {
    auto [r, c] = bot.pos(100);
    if (r * 2 == ROWS - 1 || c * 2 == COLS - 1) continue;

    ++quads[(r * 2 < ROWS - 1 ? 0 : 2) + (c * 2 < COLS - 1 ? 0 : 1)];
  }
  cout << quads[0] * quads[1] * quads[2] * quads[3] << endl;
}