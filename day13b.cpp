#include "./setup.h"

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int main() {
  ll sum = 0;
  while (!cin.eof()) {
    auto readButton = []() {
      ll x, y;
      char _c; string _t;
      cin >> _t >> _t >> _c >> _c >> x >> _c >> _c >> _c >> y;
      return make_pair(x, y);
    };
    auto readPrize = []() {
      ll x, y;
      char _c; string _t;
      cin >> _t >> _c >> _c >> x >> _c >> _c >> _c >> y;
      return make_pair(x + 10000000000000LL, y + 10000000000000LL);
    };
    auto [ax, ay] = readButton();
    auto [bx, by] = readButton();
    auto [px, py] = readPrize();
    if (cin.eof()) break;
    
    cin.ignore(1000, '\n');

    // since 2 x 2 system of equations only one solution
    // do linear algebra, check if integral
    // use cramers rule
    ll den = ax * by - bx * ay;
    ll inum = px * by - bx * py;
    ll jnum = ax * py - px * ay;

    if (inum % den || jnum % den || inum * den < 0 || jnum * den < 0) continue;

    ll i = inum / den;
    ll j = jnum / den;
    sum += i * 3 + j;
  }
  cout << sum << endl;
}