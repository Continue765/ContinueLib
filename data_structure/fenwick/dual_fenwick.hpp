#pragma once
#include <data_structure/fenwick/fenwick.hpp>

template <typename Mono>
struct DualFenwick {
    using X = typename Mono::Type;

    int n;
    Fenwick<Mono> fen;

    DualFenwick() : n(0), fen(0) {}
    DualFenwick(int n_) {
        init(n_);
    }

    void init(int n_) {
        n = n_;
        fen.init(n);
    }

    void add(int l, int r, const X& v) {
        assert(0 <= l && l <= r && r <= n);
        fen.add(l, v);
        if (r < n) {
            fen.add(r, Mono::inv(v));
        }
    }

    X query(int x) {
        assert(0 <= x && x < n);
        return fen.sum(x + 1);
    }
};
