#pragma once
#include <common.hpp>

template <typename T>
struct MaxFlow {
    struct Edge_ {
        int to;
        T cap;
        Edge_(int to_, T cap_) : to(to_), cap(cap_) {}
    };

    int n;
    vector<Edge_> e;
    vector<vector<int>> adj;
    vector<int> cur, level;

    MaxFlow() {}
    MaxFlow(int n_) {
        init(n_);
    }

    void init(int n_) {
        n = n_;
        e.clear();
        adj.assign(n_, {});
        cur.resize(n_);
        level.resize(n_);
    }

    bool bfs(int s, int t) {
        level.assign(n, -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            const int u = q.front();
            q.pop();
            for (auto& i : adj[u]) {
                auto [v, c] = e[i];
                if (c > 0 && level[v] == -1) {
                    level[v] = level[u] + 1;
                    if (v == t) {
                        return true;
                    }
                    q.push(v);
                }
            }
        }
        return false;
    }

    T dfs(int u, int t, T f) {
        if (u == t) {
            return f;
        }
        auto r = f;
        for (int& i = cur[u]; i < int(adj[u].size()); i++) {
            const int& j = adj[u][i];
            auto [v, c] = e[j];
            if (c > 0 && level[v] == level[u] + 1) {
                auto a = dfs(v, t, min(r, c));
                e[j].cap -= a;
                e[j ^ 1].cap += a;
                r -= a;
                if (r == 0) {
                    return f;
                }
            }
        }
        return f - r;
    }

    void addEdge(int u, int v, T c) {
        adj[u].push_back(e.size());
        e.emplace_back(v, c);
        adj[v].push_back(e.size());
        e.emplace_back(u, 0);
    }

    T flow(int s, int t) {
        T ans = 0;
        while (bfs(s, t)) {
            cur.assign(n, 0);
            ans += dfs(s, t, numeric_limits<T>::max());
        }
        return ans;
    }

    vector<bool> minCut() {
        vector<bool> c(n);
        for (int i = 0; i < n; i++) {
            c[i] = (level[i] != -1);
        }
        return c;
    }

    struct Edge {
        int from;
        int to;
        T cap;
        T flow;
    };

    vector<Edge> edges() {
        vector<Edge> a;
        for (int i = 0; i < e.size(); i += 2) {
            Edge x;
            x.from = e[i + 1].to;
            x.to = e[i].to;
            x.cap = e[i].cap + e[i + 1].cap;
            x.flow = e[i + 1].cap;
            a.push_back(x);
        }
        return a;
    }
};
