#pragma once
#include <data_structure/binary_lifting.hpp>

template <typename Mono>
struct TreeLifting {
    using X = typename Mono::Type;

    vector<int> dep, dfn;
    BinaryLifting<Mono> lift;

    TreeLifting() {}

    template <typename T>
    TreeLifting(vector<vector<pair<int, T>>>& adj, int root = 0) {
        init(adj, root);
    }

    template <typename T>
    void init(vector<vector<pair<int, T>>>& adj, int root) {
        int n = adj.size();
        int cur = 0;
        dep.assign(n, 0);
        dfn.assign(n, 0);
        lift.init(n);
        auto dfs = [&](auto&& self, int u, int p) -> void {
            dfn[u] = cur++;
            for (auto& [v, w] : adj[u]) {
                if (v == p) {
                    continue;
                }
                dep[v] = dep[u] + 1;
                lift.add(v, u, Mono::from(w));
                self(self, v, u);
            }
        };
        lift.add(root, -1, Mono::e());
        dfs(dfs, root, -1);
        lift.build();
    }

    int lca(int u, int v) {
        if (dep[u] < dep[v]) {
            swap(u, v);
        }
        u = lift.jump(u, dep[u] - dep[v]);
        if (u == v) {
            return u;
        }
        for (int k = lift.logn; k >= 0; k--) {
            if (lift.nxt[k][u] != lift.nxt[k][v]) {
                u = lift.nxt[k][u];
                v = lift.nxt[k][v];
            }
        }
        return lift.nxt[0][u];
    }

    pair<int, X> query(int u, int v) {
        int l = lca(u, v);
        X res = Mono::op(lift.query(u, dep[u] - dep[l]).second, lift.query(v, dep[v] - dep[l]).second);
        return {l, res};
    }
};
