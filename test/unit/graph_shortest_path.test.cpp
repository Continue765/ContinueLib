#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "graph/shortest_path/dijkstra.hpp"
#include "graph/shortest_path/bfs_01.hpp"
#include "graph/shortest_path/bellman_ford.hpp"
#include "graph/shortest_path/spfa.hpp"
#include "graph/shortest_path/floyd.hpp"
#include "graph/shortest_path/restore_path.hpp"

int main() {
    Digraph<int> adj(5);
    auto add = [&](int u, int v, int w) { adj.add(u, v, w); };
    add(0, 1, 0); add(0, 2, 4); add(1, 2, 1); add(1, 3, 2);
    add(2, 3, 0); add(3, 1, 1);
    auto [d, pre] = dijkstra(adj, 0);
    assert((d == vector<int>{0, 0, 1, 1, inf<int>}));
    assert((restorePath(pre, 3) == vector<int>{0, 1, 2, 3}));
    auto [dd, ppre] = dijkstraDense(adj, 0);
    assert(dd == d && ppre[0] == -1);
    vector<int> sources{0, 4};
    auto [md, mp, root] = dijkstra(adj, sources);
    assert(md[3] == 1 && md[4] == 0 && root[3] == 0 && root[4] == 4);
    auto [bd, bp] = bellmanFord(adj, 0);
    auto [sd, sp] = spfa(adj, 0);
    assert(bd == d && sd == d && bp[0] == -1 && sp[0] == -1);
    auto all = floyd(adj);
    for (int v = 0; v < 5; ++v) assert(all[0][v] == d[v]);
    vector<vector<int>> raw(4, vector<int>(4, inf<int>));
    for (int i = 0; i < 4; ++i) raw[i][i] = 0;
    raw[0][1] = 5; raw[0][2] = 20; raw[1][2] = -2; raw[2][3] = 3;
    floyd(raw);
    assert(raw[0][2] == 3 && raw[0][3] == 6 && raw[3][0] == inf<int>);
    Digraph<int> neg(3);
    neg.add(0, 1, 1); neg.add(1, 2, -3); neg.add(2, 1, 1);
    assert(bellmanFord(neg, 0).first.empty());
    assert(spfa(neg, 0).first.empty());
    // 权重与边编号不同，且存在重边。
    Undigraph<int> undirected(4);
    undirected.add(0, 1, 9); undirected.add(0, 1, 2); undirected.add(1, 2, 3);
    auto expected = vector<int>{5, 3, 0, inf<int>};
    assert(dijkstra(undirected, 2).first == expected);
    assert(dijkstraDense(undirected, 2).first == expected);
    assert(bellmanFord(undirected, 2).first == expected);
    assert(spfa(undirected, 2).first == expected);
    assert(floyd(undirected)[2] == expected);
    Digraph<int> binary(4);
    binary.add(0, 1, 1); binary.add(0, 1, 0); binary.add(1, 2, 1);
    assert((bfs_01(binary, 0).first == vector<int>{0, 0, 1, inf<int>}));
    vector<int> starts{0, 3};
    auto [dist, parent, roots] = bfs_01(binary, starts);
    auto [multi, multiParent, multiRoot] = dijkstra(binary, starts);
    assert((dist == vector<int>{0, 0, 1, 0}));
    assert(dist == multi && roots == multiRoot && roots[2] == 0 && roots[3] == 3);
    mt19937 rng(12376);
    for (int it = 0; it < 500; it++) {
        int n = 1 + rng() % 12;
        Digraph<int> g(n);
        vector<vector<int>> expected(n, vector<int>(n, inf<int>));
        for (int i = 0; i < n; i++) expected[i][i] = 0;
        for (int j = 0, m = rng() % 50; j < m; j++) {
            int u = rng() % n, v = rng() % n, w = rng() % 2;
            g.add(u, v, w);
            expected[u][v] = min(expected[u][v], w);
        }
        for (int k = 0; k < n; k++) for (int u = 0; u < n; u++) for (int v = 0; v < n; v++) {
            if (expected[u][k] != inf<int> && expected[k][v] != inf<int>) {
                expected[u][v] = min(expected[u][v], expected[u][k] + expected[k][v]);
            }
        }
        vector<int> sources;
        for (int j = 0, m = rng() % (n + 2); j < m; j++) sources.push_back(rng() % n);
        auto [dd, dp, dr] = dijkstra(g, sources);
        auto [bd, bp, br] = bfs_01(g, sources);
        for (int v = 0; v < n; v++) {
            int want = inf<int>;
            for (int u : sources) want = min(want, expected[u][v]);
            assert(dd[v] == want && bd[v] == want);
            for (int root : {dr[v], br[v]}) {
                if (want == inf<int>) assert(root == -1);
                else assert(find(sources.begin(), sources.end(), root) != sources.end() && expected[root][v] == want);
            }
        }
        int u = rng() % n;
        assert(dijkstraDense(g, u).first == expected[u]);
        assert(spfa(g, u).first == expected[u]);
        assert(bellmanFord(g, u).first == expected[u]);
    }
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
