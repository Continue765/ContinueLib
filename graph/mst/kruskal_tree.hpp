#pragma once
#include <graph/graph.hpp>
#include <data_structure/dsu.hpp>

template <typename T>
struct KruskalTree {
    int n, root;
    vector<i64> val;
    vector<Edge<T>> edges;
    vector<vector<int>> adj;

    KruskalTree() : n(0) {}
    KruskalTree(Graph<T, false>& g) {
        init(g);
    }

    void init(Graph<T, false>& g) {
        n = g.n;
        root = n - 1;
        val.assign(2 * n - 1, 0);
        adj.assign(2 * n - 1, vector<int>{});
        edges = g.edges;
    }

    void build() {
        DSU dsu(2 * n - 1);
        vector<int> ord(int(edges.size()));
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int x, int y) {
            return edges[x].w < edges[y].w;
        });

        for (auto& id : ord) {
            auto& e = edges[id];
            int u = e.u, v = e.v;
            i64 w = e.w;

            if (!dsu.same(u, v)) {
                u = dsu.find(u);
                v = dsu.find(v);
                val[++root] = w;

                adj[root].push_back(u);
                adj[root].push_back(v);
                adj[u].push_back(root);
                adj[v].push_back(root);

                dsu.f[u] = root;
                dsu.f[v] = root;
                dsu.siz[root] = dsu.siz[u] + dsu.siz[v];

                if (root == 2 * n - 2) {
                    return;
                }
            }
        }
    }
};