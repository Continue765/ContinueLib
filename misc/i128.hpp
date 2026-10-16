#pragma once
#include <common.hpp>

using i128 = __int128;

ostream& operator<<(ostream& os, i128 n) {
    if (n == 0) {
        return os << 0;
    }
    bool neg = n < 0;
    u128 x = neg ? u128(0) - u128(n) : u128(n);
    string s;
    while (x > 0) {
        s += char('0' + x % 10);
        x /= 10;
    }
    if (neg) s += '-';
    reverse(s.begin(), s.end());
    return os << s;
}

i128 toi128(const string& s) {
    bool neg = !s.empty() && s[0] == '-';
    int start = !s.empty() && (s[0] == '-' || s[0] == '+');
    i128 n = 0;
    for (int i = start; i < int(s.size()); i++) {
        int d = s[i] - '0';
        n = neg ? n * 10 - d : n * 10 + d;
    }
    return n;
}

i128 sqrti128(i128 n) {
    assert(n >= 0);
    i128 lo = 0, hi = i128(1) << 64;
    while (lo < hi) {
        i128 x = (lo + hi + 1) / 2;
        if (x <= n / x) {
            lo = x;
        } else {
            hi = x - 1;
        }
    }
    return lo;
}

i128 gcd(i128 a, i128 b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}
