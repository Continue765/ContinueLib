#define PROBLEM "https://judge.yosupo.jp/problem/scc"
#include <common.hpp>
#include "graph/components/scc.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    Digraph<int> g(n);
    while (m--) { int u, v; cin >> u >> v; g.add(u, v); }
    auto [count, id] = SCC(g);
    vector<vector<int>> comp(count);
    for (int u = 0; u < n; ++u) comp[id[u]].push_back(u);
    cout << count << '\n';
    for (auto& c : comp) { cout << c.size(); for (int u : c) cout << ' ' << u; cout << '\n'; }
}
