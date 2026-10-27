#pragma once
#include <graph/graph.hpp>

template <typename T>
vector<int> toPrufer(const Undigraph<T>& tree) {
    int n = tree.n;
    vector<int> fa(n, -1);
    auto dfs = [&](auto&& self, int u) -> void {
        for (auto& [v, id] : tree[u]) {
            if (v == fa[u]) {
                continue;
            }
            fa[v] = u;
            self(self, v);
        }
    };
    dfs(dfs, n - 1);
    auto deg = degree(tree);
    vector<int> prufer(n - 1);
    int p = 0, leaf = -1;
    for (int i = 0; i < n - 1; i++) {
        if (leaf == -1) {
            while (deg[p] != 1) {
                p++;
            }
            leaf = p;
        }
        int u = fa[leaf];
        prufer[i] = u;
        deg[leaf]--;
        deg[u]--;
        leaf = (deg[u] == 1 && u < p ? u : -1);
    }
    return prufer;
}

Undigraph<int> fromPrufer(const vector<int>& prufer) {
    int n = prufer.size() + 1;
    Undigraph<int> tree(n);
    vector<int> deg(n, 1);
    for (int u : prufer) {
        deg[u]++;
    }
    int p = 0, leaf = -1;
    for (int u : prufer) {
        if (leaf == -1) {
            while (deg[p] != 1) {
                p++;
            }
            leaf = p;
        }
        tree.add(leaf, u);
        deg[leaf]--;
        deg[u]--;
        leaf = (deg[u] == 1 && u < p ? u : -1);
    }
    return tree;
}
