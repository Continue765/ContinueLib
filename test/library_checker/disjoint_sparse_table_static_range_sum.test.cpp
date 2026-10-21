#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"
#include <algebra/monoid.hpp>
#include <data_structure/disjoint_spase_table.hpp>

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<i64> a(n);
    for (auto& x : a) cin >> x;
    DisjointSparseTable<AddMono<i64>> st(a);
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << st.query(l, r) << '\n';
    }
}
