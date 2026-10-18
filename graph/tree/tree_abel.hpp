#pragma once
#include <data_structure/fenwick/dual_fenwick.hpp>
#include <data_structure/fenwick/fenwick.hpp>
#include <graph/tree/hld.hpp>

template <typename T, typename Abel, bool edge = false>
struct TreeAbel {
    using X = typename Abel::Type;

    int n;
    HLD<T>& hld;
    Tree<T>& tree;
    Fenwick<Abel> sub;
    DualFenwick<Abel> path;

    TreeAbel(HLD<T>& hld_) : hld(hld_), tree(hld_.tree), n(hld_.tree.n), sub(n), path(n) {}
    TreeAbel(HLD<T>& hld_, const vector<X>& init) : hld(hld_), tree(hld_.tree), n(hld_.tree.n), sub(n), path(n) {
        assert(int(init.size()) == n - edge);
        for (int i = 0; i < int(init.size()); i++) {
            int u = i;
            if constexpr (edge) {
                u = tree.eToV(i);
            }
            path.add(tree.in[u], tree.out[u], init[i]);
            sub.add(tree.in[u], init[i]);
        }
    }

    X rootQuery(int u) {
        return path.query(tree.in[u]);
    }

    X pathQuery(int u, int v) {
        int l = hld.lca(u, v);
        X x = rootQuery(l);
        X res = Abel::op(rootQuery(u), rootQuery(v));
        res = Abel::op(res, Abel::inv(Abel::op(x, x)));
        if constexpr (!edge) {
            res = Abel::op(res, sub.rangeSum(tree.in[l], tree.in[l] + 1));
        }
        return res;
    }

    X subtreeQuery(int u, int root = -1) {
        if (root == -1) {
            root = tree.root;
        }
        if (root == u) {
            return sub.sum(n);
        }
        if (!hld.isAncester(u, root)) {
            return sub.rangeSum(tree.in[u] + edge, tree.out[u]);
        }
        int v = hld.jump(root, tree.dep[root] - tree.dep[u] - 1);
        return Abel::op(sub.rangeSum(0, tree.in[v]), sub.rangeSum(tree.out[v], n));
    }
};