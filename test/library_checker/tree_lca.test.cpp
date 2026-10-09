#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#include <common.hpp>
#include "graph/lca.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n);
    for (int v = 1; v < n; ++v) { int p; cin >> p; adj[p].push_back(v); adj[v].push_back(p); }
    LCA lca(adj);
    while (q--) { int u, v; cin >> u >> v; cout << lca.get(u, v) << '\n'; }
}
