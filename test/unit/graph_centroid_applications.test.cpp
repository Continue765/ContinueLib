#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#define main nearestRedMain
#include "../luogu/centroid_nearest_red.cpp"
#undef main
#define main countPairsMain
#include "../luogu/P4178.cpp"
#undef main

std::string run(int (*solve)(), const std::string& input) {
    std::istringstream in(input);
    std::ostringstream out;
    auto* oldIn = std::cin.rdbuf(in.rdbuf());
    auto* oldOut = std::cout.rdbuf(out.rdbuf());
    std::cin.clear();
    assert(solve() == 0);
    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);
    std::cin.clear();
    return out.str();
}

int main() {
    std::ios::sync_with_stdio(false);
    std::mt19937 rng(4178);
    for (int it = 0; it < 300; it++) {
        int n = 1 + rng() % 50;
        Undigraph<int> g(n);
        std::ostringstream edges, weighted;
        for (int v = 1; v < n; v++) {
            int u = it % 3 == 0 ? v - 1 : it % 3 == 1 ? 0 : int(rng() % v);
            int w = rng() % 30;
            g.add(u, v, w);
            edges << u + 1 << ' ' << v + 1 << '\n';
            weighted << u + 1 << ' ' << v + 1 << ' ' << w << '\n';
        }
        std::vector dist(n, std::vector<int>(n)), hops = dist;
        for (int s = 0; s < n; s++) {
            std::vector<int> par(n, -1), order{s};
            for (int i = 0; i < n; i++) {
                int u = order[i];
                for (auto [v, id] : g.adj[u]) if (v != par[u]) {
                    par[v] = u;
                    hops[s][v] = hops[s][u] + 1;
                    dist[s][v] = dist[s][u] + g.edges[id].w;
                    order.push_back(v);
                }
            }
        }
        int k = rng() % 150, pairs = 0;
        for (int u = 0; u < n; u++) for (int v = u + 1; v < n; v++) pairs += dist[u][v] <= k;
        std::string input = std::to_string(n) + '\n' + weighted.str() + std::to_string(k) + '\n';
        assert(run(countPairsMain, input) == std::to_string(pairs) + '\n');
        std::vector<int> red(n);
        red[0] = 1;
        std::ostringstream queries, expected;
        for (int q = 0; q < 100; q++) {
            int u = rng() % n;
            if (rng() % 2) {
                queries << "1 " << u + 1 << '\n';
                red[u] = 1;
            } else {
                queries << "2 " << u + 1 << '\n';
                int ans = n;
                for (int v = 0; v < n; v++) if (red[v]) ans = std::min(ans, hops[u][v]);
                expected << ans << '\n';
            }
        }
        input = std::to_string(n) + " 100\n" + edges.str() + queries.str();
        assert(run(nearestRedMain, input) == expected.str());
    }
    int a, b;
    if (std::cin >> a >> b) std::cout << a + b << '\n';
}
