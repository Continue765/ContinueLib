#pragma once
#include <data_structure/fenwick/fenwick.hpp>

template <typename Mono>
struct FenwickRangeAdd {
    using X = typename Mono::Type;

    int n;
    Fenwick<Mono> fen0, fen1;

    FenwickRangeAdd() : n(0), fen0(1), fen1(1) {}
    FenwickRangeAdd(int n_) {
        init(n_);
    }

    void init(int n_) {
        n = n_;
        fen0.init(n + 1);
        fen1.init(n + 1);
    }

    void add(int l, int r, const X& v) {
        assert(0 <= l && l <= r && r <= n);
        fen0.add(l, Mono::power(v, -static_cast<i64>(l)));
        fen0.add(r, Mono::power(v, static_cast<i64>(r)));
        fen1.add(l, v);
        fen1.add(r, Mono::inv(v));
    }

    X sum(int r) {
        assert(0 <= r && r <= n);
        return Mono::op(Mono::power(fen1.sum(r), static_cast<i64>(r)), fen0.sum(r));
    }

    X rangeSum(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        return Mono::op(Mono::inv(sum(l)), sum(r));
    }
};
