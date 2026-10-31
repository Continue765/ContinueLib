#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "algebra/act.hpp"
#include "data_structure/segment_tree/dynamic_segment_tree.hpp"

struct AffineTag {
    using Type = pair<i64, i64>;
    static Type e() { return {1, 0}; }
    static Type op(Type a, Type b) {
        return {b.first * a.first, b.first * a.second + b.second};
    }
};

struct SumAffine {
    using Mono = AddMono<i64>;
    using Tag = AffineTag;
    using X = i64;
    using Y = Tag::Type;
    static X act(X x, Y f, int len) { return f.first * x + f.second * len; }
};

void randomTest() {
    mt19937 rng(4178765);
    DynamicSegmentTree<SumAffine> seg;
    for (int it = 0; it < 100; it++) {
        int n = 1 + rng() % 80;
        vector<i64> a(n);
        if (it % 2) {
            for (auto& x : a) x = rng() % 20;
            seg = DynamicSegmentTree<SumAffine>(a);
        } else {
            seg = DynamicSegmentTree<SumAffine>(n);
            assert(seg.info.size() == 1);
        }
        assert(seg.query(0, n) == accumulate(a.begin(), a.end(), 0LL));
        for (int q = 0; q < 1000; q++) {
            int l = rng() % (n + 1), r = rng() % (n + 1);
            if (l > r) swap(l, r);
            int op = rng() % 4;
            i64 x = rng() % 20;
            if (op == 0) {
                // 赋值与加法的复合不交换，必须验证标记顺序。
                i64 mul = rng() % 2;
                seg.apply(l, r, {mul, x});
                for (int j = l; j < r; j++) a[j] = a[j] * mul + x;
            } else if (op == 1 && l < n) {
                seg.modify(l, x);
                a[l] = x;
            } else if (op == 2) {
                assert(seg.query(l, r) == accumulate(a.begin() + l, a.begin() + r, 0LL));
            } else {
                int first = -1, last = -1;
                for (int j = l; j < r; j++) if (a[j] > 0) {
                    if (first == -1) first = j;
                    last = j;
                }
                auto pred = [](i64 sum) { return sum > 0; };
                assert(seg.findFirst(l, r, pred) == first);
                assert(seg.findLast(l, r, pred) == last);
            }
            i64 seed = rng() % 10, limit = seed + rng() % 500;
            auto pred = [&](i64 sum) { return sum <= limit; };
            int right = l;
            i64 expected = seed;
            while (right < n && pred(expected + a[right])) expected += a[right++];
            i64 acc = seed;
            assert(seg.maxRight(l, pred, acc) == right && acc == expected);
            int left = r;
            expected = seed;
            while (left > 0 && pred(a[left - 1] + expected)) expected += a[--left];
            acc = seed;
            assert(seg.minLeft(r, pred, acc) == left && acc == expected);
        }
    }
    seg = DynamicSegmentTree<SumAffine>(1000000000);
    seg.apply(123456789, 987654321, {1, 2});
    assert(seg.query(0, 1000000000) == 2LL * (987654321 - 123456789));
    assert(seg.info.size() < 1000);
}

int main() {
    randomTest();
    constexpr int n = 19;
    DynamicSegmentTree<SumAdd<long long>> seg(n);
    vector<long long> a(n);
    seg.apply(2, 16, 4);
    for (int i = 2; i < 16; ++i) a[i] += 4;
    seg.apply(7, 19, 1);
    for (int i = 7; i < 19; ++i) ++a[i];
    seg.modify(0, 8);
    a[0] = 8;
    seg.modify(18, 6);
    a[18] = 6;
    auto sum = [&](int l, int r) { return accumulate(a.begin() + l, a.begin() + r, 0LL); };
    for (int l = 0; l <= n; ++l) {
        for (int r = l; r <= n; ++r) assert(seg.query(l, r) == sum(l, r));
    }
    assert(seg.findFirst(0, n, [](long long x) { return x >= 8; }) == 0);
    assert(seg.findLast(0, n, [](long long x) { return x > 0; }) == 18);
    assert(seg.findFirst(1, 2, [](long long x) { return x > 0; }) == -1);
    assert(seg.info.size() < 4 * n);

    int x, y;
    if (cin >> x >> y) cout << x + y << '\n';
}
