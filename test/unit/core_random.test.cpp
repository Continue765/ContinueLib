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
        Fenwick<AddMono<long long>> fw(a);
        SegmentTree<AddMono<long long>> seg(a);
        for (int it = 0; it < 200; ++it) {
            int l = rng() % n, r = rng() % n;
            if (l > r) swap(l, r);
            ++r;
            long long sum = accumulate(a.begin() + l, a.begin() + r, 0LL);
            assert(fw.query(l, r) == sum);
            assert(seg.query(l, r) == sum);
            int p = rng() % n;
            a[p] = (int)rng() % 101 - 50;
            seg.modify(p, a[p]);
            fw = Fenwick<AddMono<long long>>(a);
        }
    }
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
