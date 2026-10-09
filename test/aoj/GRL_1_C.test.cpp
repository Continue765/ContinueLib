#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_C"
#include <common.hpp>
#include "graph/shortest_path/floyd.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, i64>>> adj(n);
    while (m--) { int u, v; i64 w; cin >> u >> v >> w; adj[u].emplace_back(v, w); }
    auto dist = floyd(adj);
    for (int i = 0; i < n; ++i) if (dist[i][i] < 0) { cout << "NEGATIVE CYCLE\n"; return 0; }
    for (auto& row : dist) { for (int j = 0; j < n; ++j) { if (j) cout << ' '; if (row[j] == inf<i64>) cout << "INF"; else cout << row[j]; } cout << '\n'; }
}
