#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "algebra/monoid.hpp"
#include "data_structure/segment_tree/segment_tree.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::vector<long long> a(n);
    for (auto& x : a) std::cin >> x;
    SegmentTree<AddMono<long long>> seg(a);
    while (q--) {
        int t, l, r;
        std::cin >> t >> l >> r;
        if (t == 0) seg.modify(l, seg.rangeQuery(l, l + 1) + r);
        else std::cout << seg.rangeQuery(l, r) << '\n';
    }
}
