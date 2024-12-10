#include "./setup.h"

int main() {
   // read file system
   string s; cin >> s;
   vector<pair<int,int>> files;
   set<pair<int,int>> gaps;
   int pos = 0;
   for (int i = 0; i < (int)s.size(); ++i) {
      int amt = (int)(s[i] - '0');
      if (i & 1) gaps.emplace(pos, amt);
      else files.emplace_back(pos, amt);
      pos += amt;
   }

   // shift files
   for (int id = (int)files.size()-1; id >= 0; --id) {
      auto &[base, bound] = files[id];

      // find big enough gap
      auto it = gaps.begin();
      while (it != gaps.end() && it->second < bound) ++it;
      if (it == gaps.end() || it->first > base) continue;
      
      // move file to gap
      auto [gapBase, gapBound] = *it;
      gaps.erase(it);
      base = gapBase;
      gapBase += bound;
      gapBound -= bound;
      if (gapBound) gaps.emplace(gapBase, gapBound);
   }

   // calculate checksum
   ll cs = 0;
   for (int id = 0; id < (int)files.size(); ++id) {
      auto &[base, bound] = files[id];
      cs += ((ll)(base + (base + bound - 1)) * (ll)bound * id) >> 1;
   }
   cout << cs << endl;
}