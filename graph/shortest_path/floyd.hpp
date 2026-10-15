#pragma once
#include <graph/graph.hpp>

template <typename T>
void floyd(vector<vector<T>>& dist) {
    int n = dist.size();
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] < inf<T> && dist[k][j] < inf<T>) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

template <typename T, bool directed>
vector<vector<T>> floyd(const Graph<T, directed>& g) {
    int n = g.n;
    vector dist(n, vector<T>(n, inf<T>));
    for (int u = 0; u < n; u++) {
        dist[u][u] = 0;
        for (auto [v, id] : g.adj[u]) {
            T w = g.edges[id].w;
            dist[u][v] = min(dist[u][v], w);
        }
    }
    floyd(dist);
    return dist;
}
