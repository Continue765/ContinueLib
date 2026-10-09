#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A"
#include <common.hpp>
#include "graph/components/block_cut_tree.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    BlockCutTree bct(n);
    while (m--) { int u, v; cin >> u >> v; bct.addEdge(u, v); }
    bct.build();
    for (int u = 0; u < n; ++u) if (bct.cut[u]) cout << u << '\n';
}
