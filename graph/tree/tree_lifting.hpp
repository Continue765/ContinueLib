#pragma once
#include <data_structure/binary_lifting.hpp>
#include <graph/tree/tree.hpp>

template <typename Mono, typename T>
struct TreeLifting {
    using X = typename Mono::Type;

    Tree<T>& tree;
    BinaryLifting<Mono> lift;

    TreeLifting(Tree<T>& tree) : tree(tree) {
        init();
    }

    void init() {
        int n = tree.n;
        lift.init(n);
        for (int v = 0; v < n; v++) {
            if (v == tree.root) {
                lift.add(v, -1, Mono::e());
            } else {
                lift.add(v, tree.fa[v], Mono::from(tree.g.edges[tree.vToE(v)].w));
            }
        }
        lift.build();
    }

    int lca(int u, int v) {
        if (tree.dep[u] < tree.dep[v]) {
            swap(u, v);
        }
        u = lift.jump(u, tree.dep[u] - tree.dep[v]);
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
        X res = Mono::op(lift.query(u, tree.dep[u] - tree.dep[l]).second, lift.query(v, tree.dep[v] - tree.dep[l]).second);
        return {l, res};
    }
};
