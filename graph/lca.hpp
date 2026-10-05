#pragma once
#include <common.hpp>

struct LCA {
    int logn, cur;
    vector<int> dep, dfn;
    vector<vector<int>> fa;

    LCA(vector<vector<int>>& adj, int root = 0) {
        init(adj, root);
    }

    void init(vector<vector<int>>& adj, int root) {
        int n = adj.size();
        cur = 0;
        logn = __lg(n);
        fa.assign(n, vector<int>(logn + 1, -1));
        dep.assign(n, 0);
        dfn.assign(n, -1);

        auto dfs = [&](auto&& self, int u, int p) -> void {
            fa[u][0] = p;
            dfn[u] = cur++;
            for (int i = 1; i <= logn; i++) {
                fa[u][i] = fa[fa[u][i - 1]][i - 1];
            }
            for (auto& v : adj[u]) {
                if (v == p) {
                    continue;
                }
                dep[v] = dep[u] + 1;
                self(self, v, u);
            }
        };

        dfs(dfs, root, root);

        for (int i = n - 1; i >= 0; i--) {
            if (fa[i][0] == -1) {
                dfs(dfs, i, i);
            }
        }
    }

    int get(int u, int v) {
        if (dep[u] < dep[v]) {
            swap(u, v);
        }
        for (int i = logn; i >= 0; i--) {
            if (dep[fa[u][i]] >= dep[v]) {
                u = fa[u][i];
            }
        }
        if (u == v) {
            return u;
        }
        for (int i = logn; i >= 0; i--) {
            if (fa[u][i] != fa[v][i]) {
                u = fa[u][i];
                v = fa[v][i];
            }
        }
        return fa[u][0];
    }

    int dist(int u, int v) {
        int res = dep[u] + dep[v] - 2 * dep[get(u, v)];
        return res;
    }
};
