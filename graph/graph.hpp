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

    auto& operator[](int u) const {
        return adj[u];
    }
};

template <typename T>
Graph<T, true> reverse(const Graph<T, true>& g) {
    Graph<T, true> rg(g.n);
    for (auto& [u, v, w] : g.edges) {
        rg.add(v, u, w);
    }
    return rg;
}

template <typename T>
vector<int> degree(const Graph<T, false>& g) {
    vector<int> deg(g.n);
    for (auto& e : g.edges) {
        deg[e.u]++;
        deg[e.v]++;
    }
    return deg;
}

template <typename T>
pair<vector<int>, vector<int>> degree(const Graph<T, true>& g) {
    vector<int> in(g.n), out(g.n);
    for (auto& e : g.edges) {
        in[e.v]++;
        out[e.u]++;
    }
    return {in, out};
}

template <typename T, bool directed>
Graph<T, directed> induced(const Graph<T, directed>& g, const vector<int>& a) {
    int n = a.size();
    vector<int> id(g.n, -1);
    for (int i = 0; i < n; i++) {
        id[a[i]] = i;
    }
    Graph<T, directed> res(n);
    for (auto& e : g.edges) {
        if (id[e.u] != -1 && id[e.v] != -1) {
            res.add(e.u, e.v, e.w);
        }
    }
    return res;
}