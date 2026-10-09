#define PROBLEM "https://judge.yosupo.jp/problem/biconnected_components"
#include <common.hpp>
#include "graph/components/block_cut_tree.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    BlockCutTree bct(n);
    vector<int> degree(n);
    while (m--) { int u, v; cin >> u >> v; bct.addEdge(u, v); ++degree[u]; ++degree[v]; }
    bct.build();
    vector<vector<int>> blocks;
    for (int k = n; k < bct.tot; ++k) {
        vector<int> block = bct.tree[k];
        sort(block.begin(), block.end());
        blocks.push_back(move(block));
    }
    for (int u = 0; u < n; ++u) if (degree[u] == 0) blocks.push_back({u});
    cout << blocks.size() << '\n';
    for (auto& block : blocks) { cout << block.size(); for (int u : block) cout << ' ' << u; cout << '\n'; }
}
