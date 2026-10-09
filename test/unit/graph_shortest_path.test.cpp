#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "graph/shortest_path/dijkstra.hpp"
#include "graph/shortest_path/bfs_01.hpp"
#include "graph/shortest_path/bellman_ford.hpp"
#include "graph/shortest_path/spfa.hpp"
#include "graph/shortest_path/floyd.hpp"
#include "graph/shortest_path/restore_path.hpp"

int main() {
    vector<vector<pair<int, int>>> adj(5);
    auto add = [&](int u, int v, int w) { adj[u].emplace_back(v, w); };
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
    auto [z, zp] = bfs_01(adj, 0);
    assert(z == d && zp[3] == 2);
    auto [mz, mzp, mr] = bfs_01(adj, sources);
    assert(mz == md && mr[3] == 0 && mr[4] == 4);
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
    vector<vector<pair<int, int>>> neg(3);
    neg[0].emplace_back(1, 1); neg[1].emplace_back(2, -3); neg[2].emplace_back(1, 1);
    assert(bellmanFord(neg, 0).first.empty());
    assert(spfa(neg, 0).first.empty());
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
