#include "./setup.h"

int main() {
    vector<int> la;
    unordered_map<int,int> count;
    int a, b;
    while (cin >> a >> b) {
        la.push_back(a);
        ++count[b];
    }
    int sum = accumulate(all(la), 0, [&](int acc, int x) {
        return acc + count[x] * x;
    });
    cout << sum << endl;
}