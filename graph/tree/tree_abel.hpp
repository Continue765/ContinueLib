#pragma once
#include <data_structure/fenwick/dual_fenwick.hpp>
#include <data_structure/fenwick/fenwick.hpp>
#include <graph/tree/hld.hpp>

template <typename T, typename Abel, bool edge = false>
struct TreeAbel {
    using X = typename Abel::Type;

    HLD<T>& hld;
    Tree<T>& tree;
    int n;
    Fenwick<Abel> sub;
    DualFenwick<Abel> path;

    TreeAbel(HLD<T>& hld_) : hld(hld_), tree(hld.tree), n(tree.n), sub(n), path(n) {}
    TreeAbel(HLD<T>& hld_, const vector<X>& init) : hld(hld_), tree(hld.tree), n(tree.n) {
        assert(int(init.size()) == n - edge);
        vector<X> a(n, Abel::e()), b(n, Abel::e());
        for (int i = 0; i < int(init.size()); i++) {
            int u = (edge ? tree.eToV(i) : i);
            a[tree.in[u]] = init[i];
        }
        for (int i = 0; i < n; i++) {
            int u = tree.seq[i], p = tree.fa[u];
            b[i] = a[i];
            if (p != -1) {
                b[i] = Abel::op(b[tree.in[p]], b[i]);
            }
        }
        sub = Fenwick<Abel>(a);
        path = DualFenwick<Abel>(b);
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
            res = Abel::op(res, sub.query(tree.in[l], tree.in[l] + 1));
        }
        return res;
    }

    X subtreeQuery(int u, int root = -1) {
        if (root == -1) {
            root = tree.root;
        }
        if (root == u) {
            return sub.query(n);
        }
        if (!hld.isAncester(u, root)) {
            return sub.query(tree.in[u] + edge, tree.out[u]);
        }
        int v = hld.jump(root, tree.dep[root] - tree.dep[u] - 1);
        return Abel::op(sub.query(0, tree.in[v]), sub.query(tree.out[v], n));
    }
};