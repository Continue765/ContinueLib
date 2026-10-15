#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#include <common.hpp>
#include "graph/lca.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    Graph<int, false> g(n);
    for (int v = 1; v < n; ++v) { int p; cin >> p; g.add(p, v); }
    Tree tree(g);
    LCA lca(tree);
    while (q--) { int u, v; cin >> u >> v; cout << lca.get(u, v) << '\n'; }
}
