#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
#include "data_structure/dsu.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    DSU dsu(n);
    while (q--) {
        int t, u, v;
        std::cin >> t >> u >> v;
        if (t == 0) dsu.merge(u, v);
        else std::cout << dsu.same(u, v) << '\n';
    }
}
