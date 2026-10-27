#pragma once
#include <graph/graph.hpp>

template <typename T>
struct RangeGraph {
    int n, tot;
    vector<Edge<T>> edges;

    RangeGraph() {}
    RangeGraph(int n_) : n(n_), tot(3 * n) {
        for (int i = 2; i < 2 * n; i++) {
            add(out(i / 2), out(i), T{});
            add(in(i), in(i / 2), T{});
        }
    }

    int out(int i) {
        return (i >= n ? i - n : n + i);
    }
    int in(int i) {
        return (i >= n ? i - n : 2 * n + i);
    }

    int add(int u, int v, T w = {1}) {
        int id = edges.size();
        edges.emplace_back(u, v, w);
        return id;
    }

    void toRange(int u, int l, int r, T w = {1}) {
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                add(u, out(l++), w);
            }
            if (r & 1) {
                add(u, out(--r), w);
            }
        }
    }

    void fromRange(int l, int r, int v, T w = {1}) {
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                add(in(l++), v, w);
            }
            if (r & 1) {
                add(in(--r), v, w);
            }
        }
    }

    void RangeToRange(int l1, int r1, int l2, int r2, T w = {1}) {
        int u = tot++;
        fromRange(l1, r1, u, w);
        toRange(u, l2, r2, T{});
    }

    Digraph<T> build() {
        Digraph<T> g(tot);
        for (auto& [u, v, w] : edges) {
            g.add(u, v, w);
        }
        return g;
    }
};