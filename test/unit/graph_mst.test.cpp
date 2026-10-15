#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "graph/mst/kruskal.hpp"
#include "graph/mst/boruvka.hpp"
#include "graph/mst/prim.hpp"
#include "graph/mst/kruskal_tree.hpp"

void checkEdges(Graph<int, false>& g, const vector<int>& ids, int cost, int count) {
    assert(int(ids.size()) == count);
    DSU dsu(g.n);
    int sum = 0;
    for (int id : ids) {
        assert(0 <= id && id < int(g.edges.size()));
        auto e = g.edges[id];
        assert(dsu.merge(e.u, e.v));
        sum += e.w;
    }
    assert(sum == cost);
}

int main() {
    Graph<int, false> g(4);
    for (auto [u, v, w] : vector<Edge<int>>{{0, 1, 4}, {0, 2, 3}, {1, 2, 1}, {1, 3, 2}, {2, 3, 5}}) {
        g.add(u, v, w);
    }
    auto [ke, kc] = kruskal(g);
    auto [be, bc] = boruvka(g);
    auto [pe, pc] = prim(g);
    assert(kc == 6 && bc == kc && pc == kc);
    checkEdges(g, ke, kc, 3);
    checkEdges(g, be, bc, 3);
    checkEdges(g, pe, pc, 3);
    auto dense = prim<int>(4, [&](int u, int v) {
        int res = inf<int>;
        for (auto [x, id] : g.adj[u]) if (x == v) res = min(res, g.edges[id].w);
        return res;
    });
    int sum = 0;
    for (auto e : dense) sum += e.w;
    assert(dense.size() == 3 && sum == 6);

    Graph<int, false> disconnected(3);
    disconnected.add(0, 1, 2);
    auto [de, dc] = kruskal(disconnected);
    auto [fe, fc] = boruvka(disconnected);
    assert(dc == 2 && fc == dc);
    checkEdges(disconnected, de, dc, 1);
    checkEdges(disconnected, fe, fc, 1);

    Graph<int, false> parallel(3);
    parallel.add(0, 1, 9); parallel.add(0, 1, -2);
    parallel.add(1, 2, 4); parallel.add(0, 2, 7);
    for (auto [ids, cost] : {kruskal(parallel), boruvka(parallel), prim(parallel)}) {
        assert(cost == 2);
        checkEdges(parallel, ids, cost, 2);
        sort(ids.begin(), ids.end());
        assert((ids == vector<int>{1, 2}));
    }
    Graph<int, false> chain(3);
    chain.add(0, 1, 4); chain.add(1, 2, 7);
    KruskalTree<int> tree(chain);
    tree.build();
    assert(tree.root == 4 && tree.val[3] == 4 && tree.val[4] == 7);
    assert(tree.adj[4].size() == 2 && tree.adj[3].size() == 3);
    Graph<int, false> single(1);
    tree.init(single);
    tree.build();
    assert(tree.root == 0 && tree.adj.size() == 1 && tree.edges.empty());
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
