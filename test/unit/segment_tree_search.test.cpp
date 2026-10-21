#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "algebra/monoid.hpp"
#include "algebra/act.hpp"
#include "data_structure/segment_tree/segment_tree.hpp"
#include "data_structure/segment_tree/lazy_segment_tree.hpp"

struct ConcatMono {
    using Type = string;
    static Type e() { return {}; }
    static Type op(const Type& a, const Type& b) { return a + b; }
};

void boundaryTest() {
    std::mt19937 rng(1431);
    for (int n = 1; n <= 40; n++) {
        std::vector<i64> a(n);
        SegmentTree<AddMono<i64>> seg(n);
        LazySegmentTree<SumAdd<i64>> lazy(n);
        for (int q = 0; q < 100; q++) {
            int l = rng() % (n + 1);
            int r = rng() % (n + 1);
            if (l > r) {
                std::swap(l, r);
            }
            i64 add = rng() % 5;
            lazy.apply(l, r, add);
            for (int i = l; i < r; i++) {
                a[i] += add;
                seg.modify(i, a[i]);
            }

            i64 seed = rng() % 10;
            i64 limit = rng() % 200;
            auto pred = [&](i64 x) { return x <= seed + limit; };
            i64 sum = seed;
            int right = l;
            while (right < n && pred(sum + a[right])) {
                sum += a[right++];
            }
            i64 acc = seed;
            assert(seg.maxRight(l, pred, acc) == right && acc == sum);
            assert(lazy.maxRight(l, [&](i64 x) { return pred(seed + x); }) == right);

            sum = seed;
            int left = r;
            while (left > 0 && pred(a[left - 1] + sum)) {
                sum += a[--left];
            }
            acc = seed;
            assert(seg.minLeft(r, pred, acc) == left && acc == sum);
            assert(lazy.minLeft(r, [&](i64 x) { return pred(x + seed); }) == left);
        }
    }

    std::vector<std::string> words{"a", "bc", "d", "efg"};
    SegmentTree<ConcatMono> seg(words);
    for (int l = 0; l <= 4; l++) {
        for (int r = l; r <= 4; r++) {
            std::string target = "seed";
            for (int i = l; i < r; i++) {
                target += words[i];
            }
            std::string acc = "seed";
            auto prefix = [&](const std::string& x) { return target.starts_with(x); };
            assert(seg.maxRight(l, prefix, acc) == r && acc == target);

            target = "seed";
            for (int i = r - 1; i >= l; i--) {
                target = words[i] + target;
            }
            acc = "seed";
            auto suffix = [&](const std::string& x) { return target.ends_with(x); };
            assert(seg.minLeft(r, suffix, acc) == l && acc == target);
        }
    }
}

int main() {
    boundaryTest();
    vector<long long> a{1, 5, 2, 7, 4, 3};
    SegmentTree<MaxMono<long long>> seg(a);
    assert(seg.query(1, 5) == 7);
    assert(seg.findFirst(1, 5, [](long long x) { return x >= 6; }) == 3);
    assert(seg.findLast(0, 5, [](long long x) { return x >= 4; }) == 4);
    assert(seg.findFirst(2, 4, [](long long x) { return x >= 8; }) == -1);
    seg.modify(3, 0);
    assert(seg.findFirst(0, 6, [](long long x) { return x >= 5; }) == 1);
    assert(seg.findLast(0, 6, [](long long x) { return x >= 5; }) == 1);

    vector<string> words{"a", "bc", "d", "efg"};
    SegmentTree<ConcatMono> concat(words);
    assert(concat.query(1, 4) == "bcdefg");
    concat.modify(2, "XY");
    assert(concat.query(0, 4) == "abcXYefg");

    int x, y;
    if (cin >> x >> y) cout << x + y << '\n';
}
