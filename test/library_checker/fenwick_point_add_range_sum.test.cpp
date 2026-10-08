#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "algebra/monoid.hpp"
#include "data_structure/fenwick/fenwick.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    Fenwick<AddMono<long long>> fw(n);
    for (int i = 0; i < n; ++i) {
        long long a;
        std::cin >> a;
        fw.add(i, a);
    }
    while (q--) {
        int t, l, r;
        std::cin >> t >> l >> r;
        if (t == 0) fw.add(l, r);
        else std::cout << fw.rangeSum(l, r) << '\n';
    }
}
