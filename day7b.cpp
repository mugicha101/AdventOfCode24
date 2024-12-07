#include "./setup.h"

inline ll concat(ll a, ll b) {
   return stoll(to_string(a) + to_string(b));
}

bool dfs(ll v, vector<ll> &vals, ll curr, int i) {
   return i == (int)vals.size() ? curr == v : curr <= v && (dfs(v, vals, curr + vals[i], i+1) || dfs(v, vals, curr * vals[i], i+1) || dfs(v, vals, concat(curr, vals[i]), i+1));
}

int main() {
   ll v;
   ll sum = 0;

   while (cin >> v) {
      char _;
      cin >> _;
      vector<ll> vals(1);
      while (cin.peek() != '\n') {
         cin >> vals.back();
         vals.emplace_back();
      }
      vals.pop_back();

      bool found = dfs(v, vals, vals[0], 1);
      sum += found ? v : 0;
   }
   cout << sum << endl;
}