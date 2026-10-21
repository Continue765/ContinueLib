#pragma once
#include <graph/graph.hpp>

template <typename T>
struct Tree {
    Graph<T, false>& g;
    int n, root;
    vector<int> fa, pe, dep, siz, in, out, seq;
    vector<T> dist;

    Tree(Graph<T, false>& g, int rt = 0) : g(g) {
        build(rt);
    }

    void build(int rt = 0) {
        n = g.n;
        root = rt;
        assert(0 <= root && root < n);
        assert(int(g.edges.size()) == n - 1);
        fa.assign(n, -1);
        pe.assign(n, -1);
        dep.assign(n, 0);
        siz.assign(n, 1);
        in.resize(n);
        out.resize(n);
        seq.resize(n);
        dist.assign(n, T{});

        int cur = 0;
        auto dfs = [&](auto&& self, int u) -> void {
            in[u] = cur;
            seq[cur++] = u;
            for (auto [v, id] : g[u]) {
                if (v == fa[u]) {
                    continue;
                }
                fa[v] = u;
                pe[v] = id;
                dep[v] = dep[u] + 1;
                dist[v] = dist[u] + g.edges[id].w;
                self(self, v);
                siz[u] += siz[v];
            }
            out[u] = cur;
        };
        dfs(dfs, root);
    }

    int eToV(int i) {
        auto& e = g.edges[i];
        return (dep[e.u] > dep[e.v] ? e.u : e.v);
    }

    int vToE(int u) {
        return pe[u];
    }

    vector<int> subtree(int u) {
        return vector<int>(seq.begin() + in[u], seq.begin() + out[u]);
    }
};