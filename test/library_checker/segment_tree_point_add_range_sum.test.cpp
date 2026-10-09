#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include <common.hpp>
#include "algebra/monoid.hpp"
#include "data_structure/segment_tree/segment_tree.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    SegmentTree<AddMono<long long>> seg(a);
    while (q--) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 0) seg.modify(l, seg.rangeQuery(l, l + 1) + r);
        else cout << seg.rangeQuery(l, r) << '\n';
    }
}
