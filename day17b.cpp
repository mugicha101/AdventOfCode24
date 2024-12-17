#include "./setup.h"

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int main() {
  // ignore register input (regs b and c are 0)
  cin.ignore(100, '\n');
  cin.ignore(100, '\n');
  cin.ignore(100, '\n');
  cin.ignore(100, '\n');
  cin.ignore(9);
  vector<int> program(1);
  while (cin >> program.back()) {
    cin.ignore(1);
    program.emplace_back();
  }
  program.pop_back();
  string programStr;
  for (int x : program) programStr += '0' + x;

  // find value of A that outputs program input
  // program:
  // 0 b = a % 8 (gets next 3 bits of a)
  // 2 b = b ^ 7
  // 4 c = a >> b
  // 6 a = a >> 3 (shifts 3 every iteration)
  // 8 b = b ^ c
  // 10 b = b ^ 7
  // 12 out b % 8
  // 14 if a goto 0
  // constraints
  // p[i] = (a[i] ^ (a >> (a[i] ^ 0b111 + i * 3))) & 0b111 for 0 < i <= 16 (p[i] refers to ith 3-bit group of program, likewise with a[i])
  // a must be 46 to 48 bits long
  // start at a = 0
  // if a[i] doesn't match p[i], must increase at a[i] at least
  // keep iterating until matches
  // doesn't handle edge case where a[15] = 0 but still passes
  ll a = 0;
  while (true) {
    // check highest a[i] that's incorrect
    // increment it
    auto getA = [&](int i) {
      return (a >> (i * 3)) & 0b111LL;
    };
    auto check = [&](int i) {
      int ai = getA(i);
      return (ll)program[i] == ((ai ^ (a >> ((ai ^ 0b111) + i * 3))) & 0b111);
    };
    int i = 15;
    while (i >= 0 && check(i)) --i;
    if (i == -1) break;

    a += 1LL << (i * 3);
  }
  cout << a << endl;
}