#pragma once
#include <graph/graph.hpp>

template <typename T, typename F>
vector<Edge<T>> prim(int n, F&& cost) {
    vector<Edge<T>> res;
    vector<T> wei(n, inf<T>);
    vector<int> pre(n);

    auto add = [&](int u) -> void {
        for (int v = 0; v < n; v++) {
            if (pre[v] == -1) {
                continue;
            }
            T w = cost(u, v);
            if (wei[v] > w) {
                wei[v] = w;
                pre[v] = u;
            }
        }
        wei[u] = inf<T>;
        pre[u] = -1;
    };

    add(0);
    for (int i = 0; i < n - 1; i++) {
        int u = min_element(wei.begin(), wei.end()) - wei.begin();
        res.emplace_back(pre[u], u, wei[u]);
        add(u);
    }

    return res;
}

template <typename T>
pair<vector<int>, T> prim(Undigraph<T>& g) {
    int n = g.n;
    vector<int> res, pre(n, -2);
    vector<T> wei(n, inf<T>);
    T cost = 0;
    auto add = [&](int u) -> void {
        for (auto& [v, id] : g[u]) {
            if (pre[v] == -1) {
                continue;
            }
            T w = g.edges[id].w;
            if (wei[v] > w) {
                wei[v] = w;
                pre[v] = id;
            }
        }
        wei[u] = inf<T>;
        pre[u] = -1;
    };
    add(0);
    for (int i = 0; i < n - 1; i++) {
        int u = min_element(wei.begin(), wei.end()) - wei.begin();
        if (wei[u] == inf<T>) {
            break;
        }
        res.push_back(pre[u]);
        cost += wei[u];
        add(u);
    }
    return {res, cost};
}
