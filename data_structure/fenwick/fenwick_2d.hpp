#pragma once
#include <common.hpp>

template <typename Mono>
struct Fenwick2D {
    using X = typename Mono::Type;

    int h, w;
    vector<X> a;

    Fenwick2D(int h_ = 0, int w_ = 0) : h(h_), w(w_), a((h + 1) * (w + 1), Mono::e()) {}

    void add(int x, int y, const X& v) {
        assert(0 <= x && x < h);
        assert(0 <= y && y < w);
        for (int i = x + 1; i <= h; i += i & -i) {
            for (int j = y + 1; j <= w; j += j & -j) {
                a[i * (w + 1) + j] = Mono::op(a[i * (w + 1) + j], v);
            }
        }
    }

    X query(int x, int y) {
        assert(0 <= x && x <= h);
        assert(0 <= y && y <= w);
        X res = Mono::e();
        for (int i = x; i > 0; i -= i & -i) {
            for (int j = y; j > 0; j -= j & -j) {
                res = Mono::op(res, a[i * (w + 1) + j]);
            }
        }
        return res;
    }

    X query(int x1, int x2, int y1, int y2) {
        assert(0 <= x1 && x1 <= x2 && x2 <= h);
        assert(0 <= y1 && y1 <= y2 && y2 <= w);
        X s22 = query(x2, y2);
        X s12 = query(x1, y2);
        X s21 = query(x2, y1);
        X s11 = query(x1, y1);
        return Mono::op(Mono::op(s22, Mono::inv(s12)), Mono::op(Mono::inv(s21), s11));
    }
};