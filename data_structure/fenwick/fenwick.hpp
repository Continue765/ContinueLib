#pragma once
#include <common.hpp>

template <typename Mono>
struct Fenwick {
    using X = typename Mono::Type;

    int n;
    vector<X> a;

    Fenwick(int n_ = 0) : n(n_), a(n, Mono::e()) {}
    Fenwick(const vector<X>& init) : n(init.size()), a(init) {
        for (int i = 1; i <= n; i++) {
            int j = i + (i & -i);
            if (j <= n) {
                a[j - 1] = Mono::op(a[j - 1], a[i - 1]);
            }
        }
    }

    void add(int x, const X& v) {
        assert(0 <= x && x < n);
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] = Mono::op(a[i - 1], v);
        }
    }

    X query(int x) {
        assert(0 <= x && x <= n);
        X res = Mono::e();
        for (int i = x; i > 0; i -= i & -i) {
            res = Mono::op(a[i - 1], res);
        }
        return res;
    }

    X query(int l, int r) {
        assert(l <= r);
        return Mono::op(Mono::inv(query(l)), query(r));
    }

    // lower_bound
    int kth(X k) {
        int x = 0;
        for (int i = 1 << __lg(n); i; i /= 2) {
            if (x + i <= n && k >= a[x + i - 1]) {
                x += i;
                k -= a[x - 1];
            }
        }
        return x;
    }
};