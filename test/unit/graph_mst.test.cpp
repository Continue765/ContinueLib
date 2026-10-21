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
    auto [tree, val] = kruskalTree(chain);
    assert(tree.n == 5 && val[3] == 4 && val[4] == 7);
    assert(tree.adj[4].size() == 2 && tree.adj[3].size() == 3);
    Graph<int, false> single(1);
    auto [singleTree, singleVal] = kruskalTree(single);
    assert(singleTree.n == 1 && singleTree.edges.empty() && singleVal.size() == 1);
    auto [forest, forestVal] = kruskalTree(disconnected);
    assert(forest.n == 4 && forest.edges.size() == 2 && forestVal[3] == 2);
    mt19937 rng(765);
    for (int it = 0; it < 300; it++) {
        int n = 1 + rng() % 25;
        Graph<int, false> random(n);
        vector<vector<int>> best(n, vector<int>(n, inf<int>));
        auto add = [&](int u, int v, int w) {
            random.add(u, v, w);
            best[u][v] = best[v][u] = min(best[u][v], w);
        };
        for (int v = 1; v < n; v++) add(v, rng() % v, int(rng() % 11) - 5);
        for (int j = 0; j < n * 3; j++) add(rng() % n, rng() % n, int(rng() % 11) - 5);
        for (int i = 0; i < n; i++) best[i][i] = -inf<int>;
        for (int k = 0; k < n; k++) for (int u = 0; u < n; u++) for (int v = 0; v < n; v++) {
            best[u][v] = min(best[u][v], max(best[u][k], best[k][v]));
        }
        auto [kt, value] = kruskalTree(random);
        vector<int> par(2 * n - 1, -1), dep(2 * n - 1), order{kt.n - 1};
        for (int i = 0; i < int(order.size()); i++) {
            int u = order[i];
            for (auto [v, id] : kt.adj[u]) if (v != par[u]) {
                par[v] = u;
                dep[v] = dep[u] + 1;
                order.push_back(v);
            }
        }
        assert(int(order.size()) == 2 * n - 1);
        for (int u = 0; u < n; u++) for (int v = u + 1; v < n; v++) {
            int x = u, y = v;
            while (dep[x] > dep[y]) x = par[x];
            while (dep[y] > dep[x]) y = par[y];
            while (x != y) { x = par[x]; y = par[y]; }
            assert(value[x] == best[u][v]);
        }
    }
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
