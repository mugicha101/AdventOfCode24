#include "./setup.h"

int main() {
   // read file system
   string s; cin >> s;
   vector<int> fs;
   int id = 0;
   for (int i = 0; i < (int)s.size(); ++i) {
      int v = i & 1 ? -1 : id++;
      int amt = (int)(s[i] - '0');
      while (amt--) {
         fs.push_back(v);
      }
   }

   // shift files
   int j = (int)fs.size()-1;
   for (int i = 0; i < j && i < (int)fs.size(); ++i) {
      if (fs[i] != -1) continue;

      while (i < j && fs[j] == -1) --j;
      swap(fs[i], fs[j--]);
   }

   // calculate checksum
   ll cs = 0;
   for (int i = 0; i < (int)fs.size() && fs[i] != -1; ++i) {
      cs += (ll)fs[i] * (ll)i;
   }
   cout << cs << endl;
}