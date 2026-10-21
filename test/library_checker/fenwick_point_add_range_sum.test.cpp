#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include <common.hpp>
#include "algebra/monoid.hpp"
#include "data_structure/fenwick/fenwick.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    Fenwick<AddMono<long long>> fw(a);
    while (q--) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 0) fw.add(l, r);
        else cout << fw.query(l, r) << '\n';
    }
}
