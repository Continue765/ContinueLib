#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "algebra/act.hpp"
#include "data_structure/segment_tree/dynamic_segment_tree.hpp"

int main() {
    constexpr int n = 19;
    DynamicSegmentTree<SumAdd<long long>> seg(n);
    vector<long long> a(n);
    seg.rangeApply(2, 16, 4);
    for (int i = 2; i < 16; ++i) a[i] += 4;
    seg.rangeApply(7, 19, 1);
    for (int i = 7; i < 19; ++i) ++a[i];
    seg.modify(0, 8);
    a[0] = 8;
    seg.modify(18, 6);
    a[18] = 6;
    auto sum = [&](int l, int r) { return accumulate(a.begin() + l, a.begin() + r, 0LL); };
    for (int l = 0; l <= n; ++l) {
        for (int r = l; r <= n; ++r) assert(seg.rangeQuery(l, r) == sum(l, r));
    }
    assert(seg.findFirst(0, n, [](long long x) { return x >= 8; }) == 0);
    assert(seg.findLast(0, n, [](long long x) { return x > 0; }) == 18);
    assert(seg.findFirst(1, 2, [](long long x) { return x > 0; }) == -1);
    assert(seg.info.size() < 4 * n);

    int x, y;
    if (cin >> x >> y) cout << x + y << '\n';
}
