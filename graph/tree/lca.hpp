#pragma once
#include <data_structure/sparse_table.hpp>
#include <graph/tree/tree.hpp>


template <typename T>
struct LCA {
    Tree<T>& tree;
    int n, logn;
    vector<vector<int>> fa;

    LCA(Tree<T>& t) : tree(t), n(tree.n), logn(__lg(n)), fa(n, vector<int>(logn + 1)) {
        for (int u = 0; u < n; u++) {
            fa[u][0] = (tree.fa[u] == -1 ? u : tree.fa[u]);
        }
        for (int k = 1; k <= logn; k++) {
            for (int u = 0; u < n; u++) {
                fa[u][k] = fa[fa[u][k - 1]][k - 1];
            }
        }
    }

    int get(int u, int v) {
        if (tree.dep[u] < tree.dep[v]) {
            swap(u, v);
        }
        for (int i = logn; i >= 0; i--) {
            if (tree.dep[fa[u][i]] >= tree.dep[v]) {
                u = fa[u][i];
            }
        }
        if (u == v) {
            return u;
        }
        for (int i = logn; i >= 0; i--) {
            if (fa[u][i] != fa[v][i]) {
                u = fa[u][i];
                v = fa[v][i];
            }
        }
        return fa[u][0];
    }

    int dist(int u, int v) {
        int res = tree.dep[u] + tree.dep[v] - 2 * tree.dep[get(u, v)];
        return res;
    }
};

template <typename T>
struct FastLCA {
    struct DfnMin {
        struct Type {
            int dfn, fa;
        };
        static Type op(const Type& a, const Type& b) {
            return a.dfn < b.dfn ? a : b;
        }
    };

    Tree<T>& tree;
    int n;
    SparseTable<DfnMin> st;

    FastLCA(Tree<T>& tree) : tree(tree), n(tree.n) {
        vector<typename DfnMin::Type> seq(n);
        for (int u = 0; u < n; u++) {
            int p = tree.fa[u] == -1 ? u : tree.fa[u];
            seq[tree.in[u]] = {tree.in[p], p};
        }
        st = SparseTable<DfnMin>(seq);
    }

    int query(int u, int v) {
        if (u == v) {
            return u;
        }
        if (tree.in[u] > tree.in[v]) {
            swap(u, v);
        }
        return st.query(tree.in[u] + 1, tree.in[v] + 1).fa;
    }

    int dist(int u, int v) {
        return tree.dep[u] + tree.dep[v] - 2 * tree.dep[query(u, v)];
    }
};