#include "./setup.h"

int main() {
   char _;
   unordered_map<int,unordered_set<int>> adj;

   while (cin.peek() != '\n') {
      int a, b;
      cin >> a >> _ >> b;
      adj[a].insert(b);
      cin.ignore(1000, '\n');
   }
   cin.ignore(1000, '\n');

   int sum = 0;
   while (cin.peek() >= '0' && cin.peek() <= '9') {
      vector<int> update(1);
      cin >> update.back();
      while (cin.peek() == ',') {
         update.emplace_back();
         cin >> _ >> update.back();
      }
      cin.ignore(1000, '\n');
      if (update.empty()) break;

      // check inversions (O(n^2) is fine)
      for (int i = 0; i < (int)update.size(); ++i) {
         for (int j = i+1; j < (int)update.size(); ++j) {
            if (adj[update[j]].contains(update[i])) goto fail;
         }
      }
      sum += update[update.size() >> 1];

      fail:
   }
   cout << sum << endl;
}