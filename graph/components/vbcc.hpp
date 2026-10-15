#pragma once
#include <graph/graph.hpp>

template <typename T>
pair<vector<vector<int>>, vector<int>> VBCC(const Graph<T, false>& g) {
    int n = g.n;
    vector<int> stk, dfn(n, -1), low(n), cut(n, false);
    vector<vector<int>> comp;
    int cur = 0;
    auto dfs = [&](auto&& self, int u, int p) -> void {
        dfn[u] = low[u] = cur++;
        int child = 0;
        for (auto [v, id] : g.adj[u]) {
            if (id == p) {
                continue;
            }
            if (dfn[v] == -1) {
                child++;
                stk.push_back(id);
                self(self, v, id);
                low[u] = min(low[u], low[v]);
                if (low[v] >= dfn[u]) {
                    if (p != -1) {
                        cut[u] = true;
                    }
                    vector<int> block;
                    while (true) {
                        int eid = stk.back();
                        stk.pop_back();
                        block.push_back(eid);
                        if (eid == id) {
                            break;
                        }
                    }
                    comp.push_back(block);
                }
            } else if (dfn[v] < dfn[u]) {
                stk.push_back(id);
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (p == -1 && child >= 2) {
            cut[u] = true;
        }
    };
    for (int u = 0; u < n; u++) {
        if (dfn[u] == -1) {
            dfs(dfs, u, -1);
        }
    }
    for (int id = 0; id < int(g.edges.size()); id++) {
        auto& e = g.edges[id];
        if (e.u == e.v) {
            comp.push_back({id});
        }
    }
    return {comp, cut};
}
