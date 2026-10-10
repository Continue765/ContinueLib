#pragma once
#include <algebra/monoid.hpp>
#include <common.hpp>
#include <graph/tree_lifting.hpp>

template <typename T>
struct VirtualTree {
    TreeLifting<AddMono<i64>>& tree;
    vector<int> nodes;
    vector<vector<pair<int, T>>> adj;

    VirtualTree(TreeLifting<AddMono<i64>>& t) : tree(t) {}

    pair<vector<int>&, vector<vector<pair<int, T>>>&> build(const vector<int>& h) {
        nodes = h;
        auto cmp = [&](int u, int v) { return tree.dfn[u] < tree.dfn[v]; };
        sort(nodes.begin(), nodes.end(), cmp);
        int m = nodes.size();
        for (int i = 1; i < m; i++) {
            nodes.push_back(tree.lca(nodes[i - 1], nodes[i]));
        }
        sort(nodes.begin(), nodes.end(), cmp);
        nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
        int n = nodes.size();
        adj.resize(n);
        for (auto& e : adj) {
            e.clear();
        }
        for (int i = 0; i < n - 1; i++) {
            int p = tree.lca(nodes[i], nodes[i + 1]);
            int u = lower_bound(nodes.begin(), nodes.end(), p, cmp) - nodes.begin();
            int v = i + 1;
            T w = tree.dep[nodes[v]] - tree.dep[p];
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }

        return {nodes, adj};
    }
};
