#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B"
#include <common.hpp>
#include "graph/shortest_path/bellman_ford.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, s;
    cin >> n >> m >> s;
    vector<vector<pair<int, i64>>> adj(n);
    while (m--) { int u, v; i64 w; cin >> u >> v >> w; adj[u].emplace_back(v, w); }
    auto [dist, pre] = bellmanFord(adj, s);
    if (dist.empty()) { cout << "NEGATIVE CYCLE\n"; return 0; }
    for (auto d : dist) { if (d == inf<i64>) cout << "INF\n"; else cout << d << '\n'; }
}
