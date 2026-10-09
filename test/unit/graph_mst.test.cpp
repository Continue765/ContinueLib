#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "graph/mst/kruskal.hpp"
#include "graph/mst/boruvka.hpp"
#include "graph/mst/prim.hpp"
#include "graph/mst/kruskal_tree.hpp"

int main() {
    vector<Edge<int>> edges{{0, 1, 4}, {0, 2, 3}, {1, 2, 1}, {1, 3, 2}, {2, 3, 5}};
    auto [ke, kc] = kruskal(edges, 4);
    auto [be, bc] = boruvka(edges, 4);
    assert(kc == 6 && bc == kc && ke.size() == 3 && be.size() == 3);
    vector<vector<pair<int, int>>> adj(4);
    for (auto e : edges) { adj[e.u].emplace_back(e.v, e.w); adj[e.v].emplace_back(e.u, e.w); }
    auto pe = prim<int>(adj);
    auto pc = prim<int>(4, [&](int u, int v) {
        for (auto [x, w] : adj[u]) if (x == v) return w;
        return inf<int>;
    });
    int p_cost = 0, pc_cost = 0;
    for (auto e : pe) p_cost += e.w;
    for (auto e : pc) pc_cost += e.w;
    assert(pe.size() == 3 && pc.size() == 3 && p_cost == 6 && pc_cost == 6);
    vector<Edge<int>> disconnected{{0, 1, 2}};
    assert(kruskal(disconnected, 3).first.size() == 1);
    assert(boruvka(disconnected, 3).first.size() == 1);
    KruskalTree<int> tree(3);
    tree.addEdge(0, 1, 4);
    tree.addEdge(1, 2, 7);
    tree.build();
    assert(tree.root == 4 && tree.val[3] == 4 && tree.val[4] == 7);
    assert(tree.adj[4].size() == 2 && tree.adj[3].size() == 3);
    tree.init(1);
    tree.build();
    assert(tree.root == 0 && tree.adj.size() == 1 && tree.edges.empty());
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
