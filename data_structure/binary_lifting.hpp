#pragma once
#include <common.hpp>

template <typename Mono>
struct BinaryLifting {
    using X = typename Mono::Type;

    int n, logn;
    vector<vector<int>> nxt;
    vector<vector<X>> info;

    BinaryLifting() : n(0) {}
    BinaryLifting(int n_) {
        init(n_);
    }

    void init(int n_) {
        n = n_;
        logn = __lg(n);
        nxt.assign(logn + 1, vector<int>(n, -1));
        info.assign(logn + 1, vector<X>(n, Mono::e()));
    }

    void add(int u, int v, const X& x) {
        assert(-1 <= v && v < n);
        nxt[0][u] = v;
        info[0][u] = x;
    }

    void build() {
        for (int k = 0; k < logn; k++) {
            for (int u = 0; u < n; u++) {
                int v = nxt[k][u];
                if (v == -1) {
                    nxt[k + 1][u] = -1;
                    info[k + 1][u] = info[k][u];
                } else {
                    nxt[k + 1][u] = nxt[k][v];
                    info[k + 1][u] = Mono::op(info[k][u], info[k][v]);
                }
            }
        }
    }

    pair<int, X> query(int u, i64 step) {
        assert(0 <= step && step < (1LL << (logn + 1)));
        X res = Mono::e();
        for (int k = logn; k >= 0 && u != -1; k--) {
            if ((step >> k) & 1) {
                res = Mono::op(res, info[k][u]);
                u = nxt[k][u];
            }
        }
        return {u, res};
    }

    int jump(int u, i64 step) {
        assert(0 <= step && step < (1LL << (logn + 1)));
        for (int k = logn; k >= 0 && u != -1; k--) {
            if ((step >> k) & 1) {
                u = nxt[k][u];
            }
        }
        return u;
    }
};