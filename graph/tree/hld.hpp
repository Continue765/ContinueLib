#pragma once
#include <graph/tree/tree.hpp>

template <typename T>
struct HLD {
    Tree<T>& tree;
    vector<int> heavy, top;

    HLD(Tree<T>& tree) : tree(tree) {
        build();
    }

    void build() {
        int n = tree.n;
        heavy.assign(n, -1);
        top.resize(n);
        for (int v = 0; v < n; v++) {
            int u = tree.fa[v];
            if (u == -1) {
                continue;
            }
            if (heavy[u] == -1 || tree.siz[v] > tree.siz[heavy[u]]) {
                heavy[u] = v;
            }
        }
        int cur = 0;
        auto dfs = [&](auto&& self, int u, int t) -> void {
            top[u] = t;
            tree.in[u] = cur;
            tree.seq[cur++] = u;
            if (heavy[u] != -1) {
                self(self, heavy[u], t);
            }
            for (auto [v, id] : tree.g[u]) {
                if (v == tree.fa[u] || v == heavy[u]) {
                    continue;
                }
                self(self, v, v);
            }
            tree.out[u] = cur;
        };
        dfs(dfs, tree.root, tree.root);
    }

    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (tree.dep[top[u]] < tree.dep[top[v]]) {
                swap(u, v);
            }
            u = tree.fa[top[u]];
        }
        return tree.dep[u] < tree.dep[v] ? u : v;
    }

    int dist(int u, int v) {
        return tree.dep[u] + tree.dep[v] - 2 * tree.dep[lca(u, v)];
    }

    int jump(int u, int k) {
        if (k > tree.dep[u]) {
            return -1;
        }
        int d = tree.dep[u] - k;
        while (tree.dep[top[u]] > d) {
            u = tree.fa[top[u]];
        }
        return tree.seq[tree.in[u] - tree.dep[u] + d];
    }

    int jump(int u, int v, int k) {
        int p = lca(u, v);
        int a = tree.dep[u] - tree.dep[p];
        int b = tree.dep[v] - tree.dep[p];
        if (k > a + b) {
            return -1;
        }
        if (k <= a) {
            return jump(u, k);
        }
        return jump(v, a + b - k);
    }

    bool isAncester(int u, int v) {
        return tree.in[u] <= tree.in[v] && tree.in[v] < tree.out[u];
    }

    int rootedParent(int root, int v) {
        if (root == v) {
            return v;
        }
        if (!isAncester(v, root)) {
            return tree.fa[v];
        }
        return jump(root, tree.dep[root] - tree.dep[v] - 1);
    }

    int rootedSize(int root, int v) {
        if (root == v) {
            return tree.n;
        }
        if (!isAncester(v, root)) {
            return tree.siz[v];
        }
        return tree.n - tree.siz[rootedParent(root, v)];
    }

    int rootedLca(int root, int u, int v) {
        return lca(root, u) ^ lca(root, v) ^ lca(u, v);
    }

    template <typename F>
    void forPath(int u, int v, bool edge, F&& f) {
        vector<pair<int, int>> down;
        while (top[u] != top[v]) {
            if (tree.dep[top[u]] > tree.dep[top[v]]) {
                f(tree.in[top[u]], tree.in[u] + 1, true);
                u = tree.fa[top[u]];
            } else {
                down.emplace_back(tree.in[top[v]], tree.in[v] + 1);
                v = tree.fa[top[v]];
            }
        }
        bool rev = tree.dep[u] > tree.dep[v];
        int l = min(tree.in[u], tree.in[v]) + edge;
        int r = max(tree.in[u], tree.in[v]) + 1;
        if (l < r) {
            f(l, r, rev);
        }
        for (int i = int(down.size()) - 1; i >= 0; i--) {
            auto [l, r] = down[i];
            f(l, r, false);
        }
    }
};
