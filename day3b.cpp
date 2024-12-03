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
    auto match = [&](int j, string p) {
        return (int)s.size() - j >= (int)p.size() && s.substr(j, p.size()) == p;
    };
    auto matchMul = [&](int j) {
        if (!match(j, "mul(")) return 0;
        
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
    bool enabled = true;
    for (int i = 0; i < (int)s.size(); ++i) {
        if (match(i, "do()")) {
            enabled = true;
        }
        if (match(i, "don't()")) {
            enabled = false;
        }
        if (enabled) {
            sum += matchMul(i);
        }
    }
    cout << sum << endl;
}