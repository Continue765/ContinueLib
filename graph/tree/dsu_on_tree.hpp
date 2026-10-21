#pragma once
#include <graph/tree/hld.hpp>

template <typename T, typename F1, typename F2, typename F3>
void dsuOnTree(const HLD<T>& hld, F1&& add, F2&& query, F3&& reset) {
    const auto& tree = hld.tree;
    for (int i = tree.n - 1; i >= 0; i--) {
        int u = tree.seq[i];
        add(u);
        for (auto& [v, id] : tree.g[u]) {
            if (v == tree.fa[u] || v == hld.he[u]) {
                continue;
            }
            for (int j = tree.in[v]; j < tree.out[v]; j++) {
                add(tree.seq[j]);
            }
        }
        query(u);
        if (hld.top[u] == u) {
            reset();
        }
    }
}