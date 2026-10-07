#pragma once
#include <common.hpp>
#include <graph/lca.hpp>

template <typename T>
struct VirtualTree {
    LCA& lca;
    vector<int> nodes;
    vector<vector<pair<int, T>>> adj;

    VirtualTree(LCA& lca) : lca(lca) {}

    pair<vector<int>&, vector<vector<pair<int, T>>>&> build(const vector<int>& h) {
        nodes = h;
        auto cmp = [&](int u, int v) { return lca.dfn[u] < lca.dfn[v]; };
        sort(nodes.begin(), nodes.end(), cmp);
        int m = nodes.size();
        for (int i = 1; i < m; i++) {
            nodes.push_back(lca.get(nodes[i - 1], nodes[i]));
        }
        sort(nodes.begin(), nodes.end(), cmp);
        nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
        int n = nodes.size();
        adj.resize(n);
        for (auto& e : adj) {
            e.clear();
        }
        for (int i = 0; i < n - 1; i++) {
            int p = lca.get(nodes[i], nodes[i + 1]);
            int u = lower_bound(nodes.begin(), nodes.end(), p, cmp) - nodes.begin();
            int v = i + 1;
            T w = lca.dep[nodes[v]] - lca.dep[p];
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }

        return {nodes, adj};
    }
};