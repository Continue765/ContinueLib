#pragma once
#include <graph/graph.hpp>
#include <data_structure/dsu.hpp>

template <typename T>
pair<vector<int>, T> kruskal(const Undigraph<T>& g) {
    vector<int> ord(g.edges.size());
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int i, int j) {
        return g.edges[i].w < g.edges[j].w;
    });

    T cost = 0;
    vector<int> res;
    DSU dsu(g.n);
    for (auto& id : ord) {
        auto& e = g.edges[id];
        if (dsu.merge(e.u, e.v)) {
            res.push_back(id);
            cost += e.w;
        }
    }
    return {res, cost};
}