#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "algebra/monoid.hpp"
#include "graph/lca.hpp"
#include "graph/hld.hpp"
#include "graph/tree_lifting.hpp"
#include "graph/virtual_tree.hpp"

int main() {
    vector<vector<int>> tree(7);
    auto edge = [&](int u, int v) { tree[u].push_back(v); tree[v].push_back(u); };
    edge(0, 1); edge(0, 2); edge(1, 3); edge(1, 4); edge(2, 5); edge(5, 6);
    LCA lca(tree);
    FastLCA fast(tree);
    HLD hld(7);
    for (int u = 0; u < 7; ++u) for (int v : tree[u]) if (u < v) hld.addEdge(u, v);
    hld.work();
    vector<int> par{0, 0, 0, 1, 1, 2, 5};
    auto naive_lca = [&](int u, int v) { vector<bool> seen(7); for (int x = u;; x = par[x]) { seen[x] = true; if (x == 0) break; } while (!seen[v]) v = par[v]; return v; };
    for (int u = 0; u < 7; ++u) for (int v = 0; v < 7; ++v) {
        int w = naive_lca(u, v);
        assert(lca.get(u, v) == w && fast.query(u, v) == w && hld.lca(u, v) == w);
        int d = lca.dep[u] + lca.dep[v] - 2 * lca.dep[w];
        assert(lca.dist(u, v) == d && fast.dist(u, v) == d && hld.dist(u, v) == d);
    }
    assert(hld.jump(6, 2) == 2 && hld.jump(6, 4) == -1);
    assert(hld.isAncester(1, 4) && !hld.isAncester(2, 4));
    assert(hld.rootedLca(3, 4, 6) == 1);
    vector<vector<pair<int, int>>> weighted(7);
    auto wedge = [&](int u, int v, int w) { weighted[u].emplace_back(v, w); weighted[v].emplace_back(u, w); };
    wedge(0, 1, 2); wedge(0, 2, 5); wedge(1, 3, 3); wedge(1, 4, 7); wedge(2, 5, 11); wedge(5, 6, 13);
    TreeLifting<AddMono<i64>> lift(weighted);
    assert((lift.lca(3, 6) == 0 && lift.query(3, 6) == pair<int, i64>(0, 34)));
    assert((lift.query(3, 4) == pair<int, i64>(1, 10)));
    VirtualTree<int> vt(lift);
    auto [nodes1, adj1] = vt.build(vector<int>{3, 4, 6});
    assert(nodes1.size() == 5 && adj1.size() == 5);
    int degree_sum = 0;
    for (auto& row : adj1) degree_sum += row.size();
    assert(degree_sum == 8);
    auto [nodes2, adj2] = vt.build(vector<int>{6});
    assert(nodes2 == vector<int>{6} && adj2.size() == 1 && adj2[0].empty());
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
