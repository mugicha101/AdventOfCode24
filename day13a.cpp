#include "./setup.h"

int main() {
  int sum = 0;
  while (!cin.eof()) {
    auto readButton = []() {
      int x, y;
      char _c; string _t;
      cin >> _t >> _t >> _c >> _c >> x >> _c >> _c >> _c >> y;
      return make_pair(x, y);
    };
    auto readPrize = []() {
      int x, y;
      char _c; string _t;
      cin >> _t >> _c >> _c >> x >> _c >> _c >> _c >> y;
      return make_pair(x, y);
    };
    auto [ax, ay] = readButton();
    auto [bx, by] = readButton();
    auto [px, py] = readPrize();
    if (cin.eof()) break;
    
    cin.ignore(1000, '\n');

    int best = INT_MAX;
    for (int i = 0; i <= 100; ++i) {
      for (int j = 0; j <= 100; ++j) {
        if ((ax * i + bx * j) != px || (ay * i + by * j) != py) continue;

        best = min(best, i * 3 + j);
      }
    }
    if (best != INT_MAX) sum += best;
  }
  cout << sum << endl;
}