#pragma once
#include <common.hpp>

#include <graph/base.hpp>
#include <data_structure/dsu.hpp>

template <typename T>
pair<vector<Edge<T>>, T> kruskal(vector<Edge<T>>& edges, int n) {
    T cost = 0;
    vector<int> ord(edges.size());
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int i, int j) {
        return edges[i].w < edges[j].w;
    });

    DSU dsu(n);
    vector<Edge<T>> res;

    for (auto& id : ord) {
        auto& e = edges[id];
        if (dsu.merge(e.u, e.v)) {
            res.push_back(e);
            cost += e.w;
        }
    }

    return {res, cost};
}
