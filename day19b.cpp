#include "./setup.h"

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int main() {
  // towel types input
  vector<string> types;
  while (cin.peek() != '\n') {
    types.emplace_back();
    cin >> types.back();
  }
  for (int i = 0; i + 1 < (int)types.size(); ++i)
    types[i].pop_back(); // remove comma
  cin.ignore(1000, '\n');
  cin.ignore(1000, '\n');

  // check patterns
  ll totalWays = 0;
  string pattern;
  while (cin >> pattern) {
    vector<ll> dp(pattern.size() + 1); // dp[i] = # of ways to form pattern[0..<i] with towel types
    dp[0] = 1;
    for (int i = 0; i < (int)pattern.size(); ++i) {
      if (dp[i] == 0) continue;

      for (string &t : types) {
        if (i + t.size() > pattern.size() || pattern.substr(i, t.size()) != t) continue;

        dp[i + t.size()] += dp[i];
      }
    }
    totalWays += dp[pattern.size()];
  }
  cout << totalWays << endl;
}