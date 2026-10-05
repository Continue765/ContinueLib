#include "../edge.hpp"

template <typename T, typename F>
vector<Edge<T>> prim(int n, F cost) {
    vector<Edge<T>> res;
    vector<T> weight(n, inf);
    vector<int> pre(n);

    auto add = [&](int u) -> void {
        for (int v = 0; v < n; v++) {
            if (pre[v] == -1) {
                continue;
            }
            T w = cost(u, v);
            if (weight[v] > w) {
                weight[v] = w;
                pre[v] = u;
            }
        }
        weight[u] = inf;
        pre[u] = -1;
    };

    add(0);
    for (int i = 0; i < n - 1; i++) {
        int u = min_element(weight.begin(), weight.end()) - weight.begin();
        res.emplace_back(pre[u], u, weight[u]);
        add(u);
    }

    return res;
}

template <typename T>
vector<Edge<T>> prim(vector<vector<pair<int, T>>>& adj) {
    int n = adj.size();
    vector<Edge<T>> res;
    vector<T> weight(n, inf);
    vector<int> pre(n);

    auto add = [&](int u) -> void {
        for (auto& [v, w] : adj[u]) {
            if (pre[v] == -1) {
                continue;
            }
            if (weight[v] > w) {
                weight[v] = w;
                pre[v] = u;
            }
        }
        weight[u] = inf;
        pre[u] = -1;
    };

    add(0);
    for (int i = 0; i < n - 1; i++) {
        int u = min_element(weight.begin(), weight.end()) - weight.begin();
        res.emplace_back(pre[u], u, weight[u]);
        add(u);
    }

    return res;
}
