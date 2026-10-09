#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
#include <common.hpp>
#include "data_structure/dsu.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    DSU dsu(n);
    while (q--) {
        int t, u, v;
        cin >> t >> u >> v;
        if (t == 0) dsu.merge(u, v);
        else cout << dsu.same(u, v) << '\n';
    }
}
