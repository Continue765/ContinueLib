#pragma once
#include <graph/mst/kruskal.hpp>

template <typename T>
pair<Graph<int, false>, vector<T>> kruskalTree(const Graph<T, false>& g) {
    int n = g.n;
    auto [ids, cost] = kruskal(g);
    int c = ids.size();

    Graph<int, false> res(n + c);
    vector<T> val(n + c);
    DSU dsu(n);
    vector<int> top(n);
    iota(top.begin(), top.end(), 0);

    for (int i = 0; i < c; i++) {
        int id = ids[i];
        int u = g.edges[id].u, v = g.edges[id].v;
        u = dsu.find(u), v = dsu.find(v);
        int p = n + i;
        res.add(p, top[u]);
        if (u != v) {
            res.add(p, top[v]);
        }
        dsu.merge(u, v);
        top[dsu.find(u)] = p;
        val[p] = g.edges[id].w;
    }

    return {res, val};
}