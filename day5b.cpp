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
      int n = update.size();
      bool ordered = true;
      for (int i = 0; ordered && i < n; ++i) {
         for (int j = i+1; ordered && j < n; ++j) {
            ordered = !adj[update[j]].contains(update[i]);
         }
      }
      if (ordered) continue;

      // toposort
      vector<vector<int>> subAdj(n);
      vector<int> indeg(n);
      for (int i = 0; i < n; ++i) {
         for (int j = 0; j < n; ++j) {
            if (!adj[update[i]].contains(update[j])) continue;

            subAdj[i].push_back(j);
            ++indeg[j];
         }
      }
      vector<int> topo;
      topo.reserve(n);
      for (int i = 0; i < n; ++i) {
         if (indeg[i] == 0) topo.push_back(i);
      }
      for (int i = 0; i < n; ++i) {
         for (int j : subAdj[topo[i]]) {
            if (--indeg[j]) continue;

            topo.push_back(j);
         }
      }
      sum += update[topo[n >> 1]];
   }
   cout << sum << endl;
}