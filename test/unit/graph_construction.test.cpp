#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <graph/difference_constraints.hpp>
#include <graph/range_graph.hpp>
#include <graph/tree/prufer.hpp>
#include <graph/shortest_path/dijkstra.hpp>

void testDifference(mt19937& rng) {
    for (int it = 0; it < 1000; it++) {
        int n = 1 + rng() % 6;
        DifferenceConstraints<int> dc(n);
        vector<tuple<int, int, int>> edges;
        auto add = [&](int u, int v, int w) { edges.emplace_back(u, v, w); };
        for (int j = 0, m = rng() % 15; j < m; j++) {
            int u = rng() % n, v = rng() % n, w = int(rng() % 9) - 4;
            int type = rng() % 3;
            if (type == 0) { dc.constraint(u, v, w); add(u, v, w); }
            if (type == 1) { dc.lowerBound(u, v, w); add(v, u, -w); }
            if (type == 2) { dc.equality(u, v, w); add(u, v, w); add(v, u, -w); }
        }
        vector<vector<int>> d(n, vector<int>(n, 1000000));
        for (int i = 0; i < n; i++) d[i][i] = 0;
        for (auto [u, v, w] : edges) d[u][v] = min(d[u][v], w);
        for (int k = 0; k < n; k++) for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
            if (d[i][k] != 1000000 && d[k][j] != 1000000) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        }
        bool feasible = true;
        for (int i = 0; i < n; i++) feasible &= d[i][i] >= 0;
        auto [ok, x] = dc.solve();
        assert(ok == feasible);
        if (ok) {
            assert(int(x.size()) == n);
            for (auto [u, v, w] : edges) assert(x[v] - x[u] <= w);
        } else assert(x.empty());
    }
}

void testRangeGraph(mt19937& rng) {
    for (int n = 1; n <= 15; n++) for (int it = 0; it < 50; it++) {
        RangeGraph<int> rg(n);
        vector<vector<int>> d(n, vector<int>(n, inf<int>));
        for (int i = 0; i < n; i++) d[i][i] = 0;
        for (int j = 0; j < 30; j++) {
            int u = rng() % n, v = rng() % n, w = rng() % 10;
            int l = rng() % (n + 1), r = rng() % (n + 1);
            int l2 = rng() % (n + 1), r2 = rng() % (n + 1);
            if (l > r) swap(l, r);
            if (l2 > r2) swap(l2, r2);
            switch (rng() % 4) {
                case 0: rg.add(u, v, w); d[u][v] = min(d[u][v], w); break;
                case 1: rg.toRange(u, l, r, w); for (int x = l; x < r; x++) d[u][x] = min(d[u][x], w); break;
                case 2: rg.fromRange(l, r, v, w); for (int x = l; x < r; x++) d[x][v] = min(d[x][v], w); break;
                default:
                    rg.RangeToRange(l, r, l2, r2, w);
                    for (int x = l; x < r; x++) for (int y = l2; y < r2; y++) d[x][y] = min(d[x][y], w);
            }
        }
        for (int k = 0; k < n; k++) for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
            if (d[i][k] != inf<int> && d[k][j] != inf<int>) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        }
        auto g = rg.build();
        for (int u = 0; u < n; u++) {
            auto dist = dijkstra(g, u).first;
            for (int v = 0; v < n; v++) assert(dist[v] == d[u][v]);
        }
    }
}

void testPrufer(mt19937& rng) {
    for (int n = 1; n <= 30; n++) for (int it = 0; it < 100; it++) {
        Undigraph<int> g(n);
        vector<vector<int>> adj(n);
        for (int v = 1; v < n; v++) {
            int u = rng() % v;
            g.add(u, v);
            adj[u].push_back(v); adj[v].push_back(u);
        }
        vector<int> deg(n);
        for (int u = 0; u < n; u++) deg[u] = adj[u].size();
        vector<int> expected;
        for (int k = 0; k < n - 1; k++) {
            int leaf = 0;
            while (leaf == n - 1 || deg[leaf] != 1) leaf++;
            int p = -1;
            for (int v : adj[leaf]) if (deg[v]) p = v;
            expected.push_back(p);
            deg[leaf]--; deg[p]--;
        }
        auto code = toPrufer(g);
        assert(code == expected);
        auto decoded = fromPrufer(code);
        auto edges = [](auto& graph) {
            vector<pair<int, int>> e;
            for (auto [u, v, w] : graph.edges) e.emplace_back(min(u, v), max(u, v));
            sort(e.begin(), e.end());
            return e;
        };
        assert(decoded.n == n && edges(decoded) == edges(g));
    }
}

int main() {
    mt19937 rng(812745);
    testDifference(rng);
    testRangeGraph(rng);
    testPrufer(rng);
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
