#pragma once
#include <common.hpp>

template <typename T>
struct Edge {
    int u, v;
    T w;
};

template <typename T = int, bool directed = true>
struct Graph {
    int n;
    vector<Edge<T>> edges;
    vector<vector<pair<int, int>>> adj;

    Graph() : n(0) {}
    Graph(int n_) : n(n_), adj(n_) {}

    int add(int u, int v, T w = {1}) {
        int id = edges.size();
        edges.emplace_back(u, v, w);
        adj[u].emplace_back(v, id);
        if constexpr (!directed) {
            adj[v].emplace_back(u, id);
        }
        return id;
    }
};

template <typename T>
Graph<T, true> reverse(Graph<T, true>& g) {
    Graph<T, true> rg(g.n);
    for (auto& [u, v, w] : g.edges) {
        rg.add(v, u, w);
    }
    return rg;
}