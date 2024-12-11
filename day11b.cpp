#include "./setup.h"

ll stones(ll val, int procs) {
  if (procs == 0) return 1;

  static map<pair<ll,int>,ll> memo;
  pair<ll,int> key = make_pair(val, procs);
  auto it = memo.find(key);
  if (it != memo.end()) {
    return it->second;
  }

  if (val == 0) {
    return memo[key] = stones(1, procs - 1);
  }
  string digs = to_string(val);
  int n = digs.size();
  if (n & 1) {
    return memo[key] = stones(val * 2024, procs - 1);
  }

  int h = n >> 1;
  return memo[key] = stones(stoi(digs.substr(0, h)), procs - 1) + stones(stoi(digs.substr(h, h)), procs - 1);
}

int main() {
  int s;
  ll sum = 0;
  while (cin >> s) {
    sum += stones(s, 75);
  }
  cout << sum << endl;
}