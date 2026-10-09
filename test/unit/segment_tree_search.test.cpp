#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "algebra/monoid.hpp"
#include "data_structure/segment_tree/segment_tree.hpp"

struct ConcatMono {
    using Type = string;
    static Type e() { return {}; }
    static Type op(const Type& a, const Type& b) { return a + b; }
};

int main() {
    vector<long long> a{1, 5, 2, 7, 4, 3};
    SegmentTree<MaxMono<long long>> seg(a);
    assert(seg.rangeQuery(1, 5) == 7);
    assert(seg.findFirst(1, 5, [](long long x) { return x >= 6; }) == 3);
    assert(seg.findLast(0, 5, [](long long x) { return x >= 4; }) == 4);
    assert(seg.findFirst(2, 4, [](long long x) { return x >= 8; }) == -1);
    seg.modify(3, 0);
    assert(seg.findFirst(0, 6, [](long long x) { return x >= 5; }) == 1);
    assert(seg.findLast(0, 6, [](long long x) { return x >= 5; }) == 1);

    vector<string> words{"a", "bc", "d", "efg"};
    SegmentTree<ConcatMono> concat(words);
    assert(concat.rangeQuery(1, 4) == "bcdefg");
    concat.modify(2, "XY");
    assert(concat.rangeQuery(0, 4) == "abcXYefg");

    int x, y;
    if (cin >> x >> y) cout << x + y << '\n';
}
