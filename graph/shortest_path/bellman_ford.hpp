#pragma once
#include <graph/graph.hpp>

template <typename T, bool directed>
pair<vector<T>, vector<int>> bellmanFord(const Graph<T, directed>& g, int s) {
    int n = g.n;
    vector<T> dist(n, inf<T>);
    vector<int> pre(n, -1);

    dist[s] = 0;

    for (int round = 1;; round++) {
        bool upd = false;
        for (int u = 0; u < n; u++) {
            if (dist[u] == inf<T>) {
                continue;
            }
            for (auto [v, id] : g[u]) {
                T w = g.edges[id].w;
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pre[v] = u;
                    upd = true;
                    if (round >= n) {
                        return {{}, {}};
                    }
                }
            }
        }
        if (!upd) {
            break;
        }
    }

    return {dist, pre};
}
