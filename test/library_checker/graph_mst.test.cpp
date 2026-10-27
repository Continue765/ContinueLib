#define PROBLEM "https://judge.yosupo.jp/problem/minimum_spanning_tree"
#include <common.hpp>
#include "graph/mst/kruskal.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    Undigraph<i64> g(n);
    for (int i = 0; i < m; ++i) { int u, v; i64 w; cin >> u >> v >> w; g.add(u, v, w); }
    auto [answer, cost] = kruskal(g);
    cout << cost << '\n';
    for (int i = 0; i < int(answer.size()); ++i) cout << answer[i] << (i + 1 == int(answer.size()) ? '\n' : ' ');
    if (answer.empty()) cout << '\n';
}
