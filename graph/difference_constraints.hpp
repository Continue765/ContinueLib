#pragma once
#include <graph/shortest_path/bellman_ford.hpp>

template <typename T>
struct DifferenceConstraints {
    int n, s;
    Graph<T, true> graph;

    DifferenceConstraints() {}
    DifferenceConstraints(int n_) : n(n_), s(n), graph(n + 1) {
        for (int u = 0; u < n; u++) {
            graph.add(s, u);
        }
    }

    // x_v - x_u <= w
    void constraint(int u, int v, T w) {
        graph.add(u, v, w);
    }

    // x_v - x_u >= w
    void lowerBound(int u, int v, T w) {
        graph.add(v, u, -w);
    }

    // x_v - x_u = w
    void equality(int u, int v, T w) {
        constraint(u, v, w);
        lowerBound(u, v, w);
    }

    pair<bool, vector<T>> solve() {
        auto [dist, pre] = bellmanFord<T>(graph, s);
        if (dist.empty()) {
            return {false, {}};
        }
        dist.pop_back();
        return {true, dist};
    }
};