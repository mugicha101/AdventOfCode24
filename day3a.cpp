#include "./setup.h"

int main() {
    string s;
    string t;
    while (cin >> t) {
        s += t;
    }
    s += ';';

    auto dig = [](char c) {
        return c >= '0' && c <= '9';
    };
    auto matchMul = [&](int j) {
        if (s.substr(j, 4) != "mul(") return 0;
        
        j += 4;
        auto matchNum = [&](int pos) {
            if (!dig(s[pos])) return make_pair(0,0);
            int num = s[pos] - '0';
            int len = 1;

            while (len < 3 && dig(s[pos+len])) {
                num = num * 10 + s[pos+len] - '0';
                ++len;
            }

            return make_pair(num, len);
        };
        auto [a, aLen] = matchNum(j);
        if (aLen == 0) return 0;

        j += aLen;
        if (s[j++] != ',') return 0;

        auto [b, bLen] = matchNum(j);
        j += bLen;
        if (s[j++] != ')') return 0;

        return a * b;
    };

    int sum = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
        sum += matchMul(i);
    }
    cout << sum << endl;
}