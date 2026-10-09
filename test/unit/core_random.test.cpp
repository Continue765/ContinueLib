#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "algebra/monoid.hpp"
#include "data_structure/fenwick/fenwick.hpp"
#include "data_structure/segment_tree/segment_tree.hpp"

int main() {
    mt19937 rng(123456789);
    for (int n = 1; n <= 32; ++n) {
        vector<long long> a(n);
        for (auto& x : a) x = (int)rng() % 101 - 50;
        Fenwick<AddMono<long long>> fw(n);
        for (int i = 0; i < n; ++i) fw.add(i, a[i]);
        SegmentTree<AddMono<long long>> seg(a);
        for (int it = 0; it < 200; ++it) {
            int l = rng() % n, r = rng() % n;
            if (l > r) swap(l, r);
            ++r;
            long long sum = accumulate(a.begin() + l, a.begin() + r, 0LL);
            assert(fw.rangeSum(l, r) == sum);
            assert(seg.rangeQuery(l, r) == sum);
            int p = rng() % n;
            a[p] = (int)rng() % 101 - 50;
            seg.modify(p, a[p]);
            fw = Fenwick<AddMono<long long>>(n);
            for (int i = 0; i < n; ++i) fw.add(i, a[i]);
        }
    }
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
