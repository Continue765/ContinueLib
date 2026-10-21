#pragma once
#include <algebra/monoid.hpp>
#include <graph/tree/tree_lifting.hpp>

template <typename T>
struct VirtualTree {
    TreeLifting<AddMono<i64>, T>& tree;
    vector<int> vt;
    vector<vector<pair<int, T>>> adj;

    VirtualTree(TreeLifting<AddMono<i64>, T>& t) : tree(t) {}

    pair<vector<int>&, vector<vector<pair<int, T>>>&> build(vector<int>& h) {
        vt = h;
        auto cmp = [&](int u, int v) { return tree.tree.in[u] < tree.tree.in[v]; };
        sort(vt.begin(), vt.end(), cmp);
        int m = vt.size();
        for (int i = 1; i < m; i++) {
            vt.push_back(tree.lca(vt[i - 1], vt[i]));
        }
        sort(vt.begin(), vt.end(), cmp);
        vt.erase(unique(vt.begin(), vt.end()), vt.end());
        int n = vt.size();
        adj.resize(n);
        for (auto& e : adj) {
            e.clear();
        }
        for (int i = 0; i < n - 1; i++) {
            int p = tree.lca(vt[i], vt[i + 1]);
            int u = lower_bound(vt.begin(), vt.end(), p, cmp) - vt.begin();
            int v = i + 1;
            T w = tree.tree.dep[vt[v]] - tree.tree.dep[p];
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }
        return {vt, adj};
    }
};
