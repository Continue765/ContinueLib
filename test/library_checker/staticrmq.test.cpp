#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include <common.hpp>
#include "algebra/monoid.hpp"
#include "data_structure/sparse_table.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<u32> a(n);
    for (auto& x : a) cin >> x;
    SparseTable<MinMono<u32>> st(a);
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << st.query(l, r) << '\n';
    }
}
