#pragma once
#include <graph/graph.hpp>

template <typename T>
pair<int, vector<int>> SCC(const Digraph<T>& g) {
    int n = g.n;
    vector<int> stk, dfn(n, -1), low(n), comp(n, -1);
    int cur = 0, cnt = 0;
    auto dfs = [&](auto&& self, int u) -> void {
        dfn[u] = low[u] = cur++;
        stk.push_back(u);
        for (auto& [v, id] : g[u]) {
            if (dfn[v] == -1) {
                self(self, v);
                low[u] = min(low[u], low[v]);
            } else if (comp[v] == -1) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (dfn[u] == low[u]) {
            int y;
            do {
                y = stk.back();
                comp[y] = cnt;
                stk.pop_back();
            } while (y != u);
            cnt++;
        }
    };
    for (int i = 0; i < n; i++) {
        if (dfn[i] == -1) {
            dfs(dfs, i);
        }
    }
    for (auto& u : comp) {
        u = cnt - 1 - u;
    }
    return {cnt, comp};
}