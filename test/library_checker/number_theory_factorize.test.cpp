#define PROBLEM "https://judge.yosupo.jp/problem/factorize"
#include <common.hpp>
#include "number_theory/pollard.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        i64 n;
        cin >> n;
        auto pf = factorize(n);
        vector<i64> factors;
        for (auto [p, e] : pf) while (e--) factors.push_back(p);
        cout << factors.size();
        for (i64 p : factors) cout << ' ' << p;
        cout << '\n';
    }
}
