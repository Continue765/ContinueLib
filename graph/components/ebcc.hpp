#pragma once
#include <common.hpp>

struct EBCC {
    int n;
    vector<vector<pair<int, int>>> adj;
    vector<int> stk;
    vector<int> dfn, low, bel;
    int cur, cnt, ecnt;

    EBCC() {}
    EBCC(int n_) {
        init(n_);
    }

    void init(int n_) {
        n = n_;
        adj.assign(n, {});
        dfn.assign(n, -1);
        low.resize(n);
        bel.assign(n, -1);
        stk.clear();
        cur = cnt = ecnt = 0;
    }

    void addEdge(int u, int v) {
        adj[u].emplace_back(v, ecnt);
        adj[v].emplace_back(u, ecnt);
        ecnt++;
    }

    void dfs(int u, int p) {
        dfn[u] = low[u] = cur++;
        stk.push_back(u);

        for (auto& [v, eid] : adj[u]) {
            if (eid == p) {
                continue;
            }
            if (dfn[v] == -1) {
                dfs(v, eid);
                low[u] = min(low[u], low[v]);
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }

        if (dfn[u] == low[u]) {
            int y;
            do {
                y = stk.back();
                bel[y] = cnt;
                stk.pop_back();
            } while (y != u);
            cnt++;
        }
    }

    vector<int> work() {
        for (int i = 0; i < n; i++) {
            if (dfn[i] == -1) {
                dfs(i, -1);
            }
        }
        return bel;
    }
};
