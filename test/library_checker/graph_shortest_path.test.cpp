#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"
#include <common.hpp>
#include "graph/shortest_path/dijkstra.hpp"
#include "graph/shortest_path/restore_path.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vector<vector<pair<int, i64>>> adj(n);
    while (m--) { int u, v; i64 w; cin >> u >> v >> w; adj[u].emplace_back(v, w); }
    auto [dist, pre] = dijkstra(adj, s);
    if (dist[t] == inf<i64>) { cout << -1 << '\n'; return 0; }
    auto path = restorePath(pre, t);
    cout << dist[t] << ' ' << path.size() - 1 << '\n';
    for (int i = 1; i < int(path.size()); ++i) cout << path[i - 1] << ' ' << path[i] << '\n';
}
