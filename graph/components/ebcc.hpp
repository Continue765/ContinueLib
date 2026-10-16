#pragma once
#include <graph/graph.hpp>

template <typename T>
pair<int, vector<int>> EBCC(const Graph<T, false>& g) {
    int n = g.n;
    vector<int> stk;
    vector<int> dfn(n, -1), low(n), comp(n, -1);
    int cur = 0, cnt = 0;
    auto dfs = [&](auto&& self, int u, int parentEdge) -> void {
        dfn[u] = low[u] = cur++;
        stk.push_back(u);
        for (auto [v, id] : g.adj[u]) {
            if (id == parentEdge) {
                continue;
            }
            if (dfn[v] == -1) {
                self(self, v, id);
                low[u] = min(low[u], low[v]);
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (dfn[u] == low[u]) {
            while (true) {
                int v = stk.back();
                stk.pop_back();
                comp[v] = cnt;
                if (v == u) {
                    break;
                }
            }
            cnt++;
        }
    };
    for (int u = 0; u < n; u++) {
        if (dfn[u] == -1) {
            dfs(dfs, u, -1);
        }
    }
    return {cnt, comp};
}