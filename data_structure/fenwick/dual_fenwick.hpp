#pragma once
#include <data_structure/fenwick/fenwick.hpp>

template <typename Abel>
struct DualFenwick {
    using X = typename Abel::Type;

    int n;
    Fenwick<Abel> fen;

    DualFenwick(int n_ = 0) : n(n_), fen(n) {}
    DualFenwick(const vector<X>& init) : n(init.size()) {
        vector<X> d(n);
        X pre = Abel::e();
        for (int i = 0; i < n; i++) {
            d[i] = Abel::op(Abel::inv(pre), init[i]);
            pre = init[i];
        }
        fen = Fenwick<Abel>(d);
    }

    void add(int l, int r, const X& v) {
        assert(0 <= l && l < r && r <= n);
        fen.add(l, v);
        if (r < n) {
            fen.add(r, Abel::inv(v));
        }
    }

    X query(int x) {
        assert(0 <= x && x < n);
        return fen.query(x + 1);
    }
};
