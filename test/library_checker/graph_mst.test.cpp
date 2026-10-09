#define PROBLEM "https://judge.yosupo.jp/problem/minimum_spanning_tree"
#include <common.hpp>
#include "graph/mst/kruskal.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<Edge<i64>> edges;
    for (int i = 0; i < m; ++i) { int u, v; i64 w; cin >> u >> v >> w; edges.emplace_back(u, v, w); }
    auto [tree, cost] = kruskal(edges, n);
    if (n > 0 && int(tree.size()) != n - 1) { cout << -1 << '\n'; return 0; }
    map<tuple<int, int, i64>, queue<int>> ids;
    for (int i = 0; i < int(edges.size()); ++i) ids[{edges[i].u, edges[i].v, edges[i].w}].push(i);
    vector<int> answer;
    for (auto e : tree) {
        auto key = tuple{e.u, e.v, e.w};
        if (ids[key].empty()) key = {e.v, e.u, e.w};
        answer.push_back(ids[key].front());
        ids[key].pop();
    }
    cout << cost << '\n';
    for (int i = 0; i < int(answer.size()); ++i) cout << answer[i] << (i + 1 == int(answer.size()) ? '\n' : ' ');
    if (answer.empty()) cout << '\n';
}
