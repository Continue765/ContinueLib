#pragma once
#include <graph/graph.hpp>

struct BlockCutTree {
    int n, tot;
    Undigraph<int> tree;

    BlockCutTree() {}
    template <typename T>
    BlockCutTree(const Undigraph<T>& g) : n(g.n), tree(n) {
        vector<int> dfn(n, -1), low(n), stk;
        int cur = 0;
        auto dfs = [&](auto&& self, int u) -> void {
            dfn[u] = low[u] = cur++;
            stk.push_back(u);
            for (auto [v, id] : g[u]) {
                if (dfn[v] == -1) {
                    self(self, v);
                    low[u] = min(low[u], low[v]);
                    if (low[v] >= dfn[u]) {
                        int b = tree.n++;
                        tree.adj.emplace_back();
                        tree.add(u, b);
                        int x;
                        do {
                            x = stk.back();
                            stk.pop_back();
                            tree.add(x, b);
                        } while (x != v);
                    }
                } else {
                    low[u] = min(low[u], dfn[v]);
                }
            }
        };
        for (int u = 0; u < n; u++) {
            if (dfn[u] == -1) {
                dfs(dfs, u);
                stk.pop_back();
            }
        }
        tot = tree.n;
    }

    bool isCut(int u) const {
        return tree[u].size() > 1;
    }
};
