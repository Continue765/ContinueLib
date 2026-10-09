#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "string/kmp.hpp"
#include "string/manacher.hpp"
#include "string/z_algo.hpp"

void test() {
    for (string s : {string(), string("a"), string("aaaaa"), string("abacaba"), string("abacaa")}) {
        auto z = Z(s);
        assert(z.size() == s.size() + 1 && z[0] == static_cast<int>(s.size()));
        auto f = kmp(s);
        assert(f.size() == s.size() + 1 && f[0] == 0);
        for (int i = 1; i <= static_cast<int>(s.size()); i++) {
            int bruteZ = 0;
            while (i + bruteZ < static_cast<int>(s.size()) && s[bruteZ] == s[i + bruteZ]) bruteZ++;
            if (i < static_cast<int>(s.size())) assert(z[i] == bruteZ);
            int brutePi = 0;
            for (int k = 1; k < i; k++) if (s.substr(0, k) == s.substr(i - k, k)) brutePi = k;
            assert(f[i] == brutePi);
        }
        auto r = manacher(s);
        string t = "#";
        for (char c : s) { t += c; t += '#'; }
        for (int i = 0; i < static_cast<int>(t.size()); i++) {
            int radius = 0;
            while (i - radius >= 0 && i + radius < static_cast<int>(t.size()) && t[i - radius] == t[i + radius]) radius++;
            assert(r[i] == radius);
        }
    }
}

int main() {
    test();
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
