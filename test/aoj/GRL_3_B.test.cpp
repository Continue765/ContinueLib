#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B"
#include <common.hpp>
#include "graph/components/ebcc.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    EBCC ebcc(n);
    vector<pair<int, int>> edges(m);
    for (auto& [u, v] : edges) { cin >> u >> v; ebcc.addEdge(u, v); }
    auto id = ebcc.work();
    vector<pair<int, int>> bridges;
    for (auto [u, v] : edges) if (id[u] != id[v]) { if (u > v) swap(u, v); bridges.emplace_back(u, v); }
    sort(bridges.begin(), bridges.end());
    for (auto [u, v] : bridges) cout << u << ' ' << v << '\n';
}
