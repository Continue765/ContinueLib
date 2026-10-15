#define PROBLEM "https://judge.yosupo.jp/problem/biconnected_components"
#include <common.hpp>
#include "graph/components/block_cut_tree.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    Graph<int, false> g(n);
    vector<int> degree(n);
    while (m--) { int u, v; cin >> u >> v; g.add(u, v); ++degree[u]; ++degree[v]; }
    BlockCutTree bct(g);
    vector<vector<int>> blocks;
    for (int k = n; k < bct.tot; ++k) {
        vector<int> block;
        for (auto [v, id] : bct.tree.adj[k]) block.push_back(v);
        sort(block.begin(), block.end());
        blocks.push_back(move(block));
    }
    for (int u = 0; u < n; ++u) if (degree[u] == 0) blocks.push_back({u});
    cout << blocks.size() << '\n';
    for (auto& block : blocks) { cout << block.size(); for (int u : block) cout << ' ' << u; cout << '\n'; }
}
