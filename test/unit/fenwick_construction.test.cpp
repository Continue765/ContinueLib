#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <algebra/monoid.hpp>
#include <data_structure/fenwick/dual_fenwick.hpp>
#include <data_structure/fenwick/fenwick_range_add.hpp>

int main() {
    mt19937 rng(87312);
    for (int n = 1; n <= 65; n++) {
        vector<i64> a(n);
        for (auto& x : a) x = int(rng() % 101) - 50;
        Fenwick<AddMono<i64>> fen(a);
        DualFenwick<AddMono<i64>> dual(a);
        FenwickRangeAdd<AddMono<i64>> range(a);
        auto check = [&]() {
            for (int i = 0; i < n; i++) assert(dual.query(i) == a[i]);
            for (int l = 0; l <= n; l++) {
                i64 sum = 0;
                for (int r = l; r <= n; r++) {
                    assert(fen.query(l, r) == sum);
                    assert(range.query(l, r) == sum);
                    if (r < n) sum += a[r];
                }
            }
        };
        check();
        for (int q = 0; q < 20; q++) {
            int l = rng() % n, r = l + 1 + rng() % (n - l);
            i64 v = int(rng() % 31) - 15;
            dual.add(l, r, v);
            range.add(l, r, v);
            for (int i = l; i < r; i++) {
                a[i] += v;
                fen.add(i, v);
            }
            check();
        }
    }
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
