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

        bool safe = true;
        if (vals[1] > vals[0]) {
            // check increasing
            for (int i = 1; safe && i < (int)vals.size(); ++i) {
                int d = vals[i] - vals[i-1];
                safe &= d >= 1 && d <= 3;
            }
        } else {
            // check for decreasing
            for (int i = 1; safe && i < (int)vals.size(); ++i) {
                int d = vals[i] - vals[i-1];
                safe &= d >= -3 && d <= -1;
            }
        }
        numSafe += safe;
    }
    cout << numSafe << endl;
}