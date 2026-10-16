#pragma once
#include <graph/graph.hpp>
#include <graph/components/vbcc.hpp>

struct BlockCutTree {
    int n, tot;
    vector<int> cut;
    Graph<int, false> tree;

    BlockCutTree() {}
    template <typename T>
    BlockCutTree(const Graph<T, false>& g) {
        init(g);
    }

    template <typename T>
    void init(const Graph<T, false>& g) {
        n = g.n;
        vector<vector<int>> comp;
        tie(comp, cut) = VBCC(g);
        tot = n + int(comp.size());
        tree = Graph<int, false>(tot);
        for (int i = 0; i < int(comp.size()); i++) {
            vector<int> node;
            for (int id : comp[i]) {
                node.push_back(g.edges[id].u);
                node.push_back(g.edges[id].v);
            }
            sort(node.begin(), node.end());
            node.erase(unique(node.begin(), node.end()), node.end());
            for (auto& u : node) {
                tree.add(u, n + i);
            }
        }
    }

    bool isCut(int u) {
        return cut[u];
    }
};