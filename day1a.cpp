#include "./setup.h"

int main() {
    vector<int> la;
    vector<int> lb;
    int a, b;
    while (cin >> a >> b) {
        la.push_back(a);
        lb.push_back(b);
    }

    int n = la.size();
    sort(all(la));
    sort(all(lb));
    int sum = 0;

    for (int i = 0; i < n; ++i) {
        sum += abs(la[i] - lb[i]);
    }
    cout << sum << endl;
}