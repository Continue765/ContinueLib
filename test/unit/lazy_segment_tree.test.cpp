#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "algebra/act.hpp"
#include "data_structure/segment_tree/lazy_segment_tree.hpp"

int main() {
    vector<long long> a{2, 1, 4, 3, 0, 5, 2};
    LazySegmentTree<SumAdd<long long>> seg(a);
    auto sum = [&](int l, int r) { return accumulate(a.begin() + l, a.begin() + r, 0LL); };
    assert(seg.rangeQuery(0, 7) == sum(0, 7));
    seg.rangeApply(1, 6, 3);
    for (int i = 1; i < 6; ++i) a[i] += 3;
    assert(seg.rangeQuery(2, 5) == sum(2, 5));
    seg.modify(4, -2);
    a[4] = -2;
    seg.rangeApply(0, 3, -1);
    for (int i = 0; i < 3; ++i) --a[i];
    for (int l = 0; l <= 7; ++l) {
        for (int r = l; r <= 7; ++r) assert(seg.rangeQuery(l, r) == sum(l, r));
    }
    assert(seg.findFirst(0, 7, [](long long x) { return x > 0; }) == 0);
    assert(seg.findLast(0, 7, [](long long x) { return x > 0; }) == 6);
    assert(seg.findFirst(4, 6, [](long long x) { return x > 0; }) == 5);
    assert(seg.findLast(1, 5, [](long long x) { return x > 100; }) == -1);

    int x, y;
    if (cin >> x >> y) cout << x + y << '\n';
}
