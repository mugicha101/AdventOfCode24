#include "./setup.h"

int main() {
    int numSafe = 0;
    while (true) {
        int x;
        vector<int> vals;
        while (cin.peek() != '\n' && cin >> x) {
            vals.push_back(x);
        }
        if (vals.empty()) break;
        cin.ignore(1000, '\n');

        int n = vals.size();

        auto check = [&]() {
            bool safe = false;
            for (int s = 0; !safe && s < n; ++s) {
                int p = -1;
                safe = true;
                for (int i = 0; safe && i < n; ++i) {
                    if (i == s) continue;
                    safe = p == -1 || (vals[i] - p >= 1 && vals[i] - p <= 3);
                    p = vals[i];
                }
            }
            return safe;
        };
        bool safe = check();
        if (!safe) {
            for (int &x : vals) x = -x;
            safe = check();
        }

        numSafe += safe;
    }
    cout << numSafe << endl;
}