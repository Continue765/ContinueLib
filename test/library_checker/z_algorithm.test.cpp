#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"
#include <common.hpp>
#include "string/z_algo.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    auto z = Z(s);
    for (int i = 0; i < (int)s.size(); ++i) cout << z[i] << (i + 1 == (int)s.size() ? '\n' : ' ');
}
