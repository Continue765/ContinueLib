#pragma once
#include <data_structure/fenwick/fenwick.hpp>

template <typename Abel>
struct FenwickRangeAdd {
    using X = typename Abel::Type;

    int n;
    Fenwick<Abel> fen0, fen1;

    FenwickRangeAdd(int n_ = 0) : n(n_), fen0(n + 1), fen1(n + 1) {}
    FenwickRangeAdd(const vector<X>& init) : n(init.size()) {
        vector<X> d(n + 1), w(n + 1);
        X pre = Abel::e();
        for (int i = 0; i <= n; i++) {
            X cur = (i < n ? init[i] : Abel::e());
            d[i] = Abel::op(Abel::inv(pre), cur);
            w[i] = Abel::pow(d[i], -i);
            pre = cur;
        }
        fen0 = Fenwick<Abel>(w);
        fen1 = Fenwick<Abel>(d);
    }

    void add(int l, int r, const X& v) {
        assert(0 <= l && l < r && r <= n);
        fen0.add(l, Abel::pow(v, -l));
        fen0.add(r, Abel::pow(v, r));
        fen1.add(l, v);
        fen1.add(r, Abel::inv(v));
    }

    X query(int r) {
        assert(0 <= r && r <= n);
        return Abel::op(Abel::pow(fen1.query(r), r), fen0.query(r));
    }

    X query(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        return Abel::op(Abel::inv(query(l)), query(r));
    }
};