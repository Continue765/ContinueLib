#pragma once
#include <common.hpp>

template <typename T>
struct Combination {
    int n;
    vector<T> fact_, invfact_, inv_;

    Combination() : n(0), fact_{1}, invfact_{1}, inv_{0} {}
    Combination(int n_) : Combination() {
        init(n_);
    }

    void init(int n_) {
        if (n_ <= n) {
            return;
        }
        fact_.resize(n_ + 1);
        invfact_.resize(n_ + 1);
        inv_.resize(n_ + 1);

        for (int i = n + 1; i <= n_; i++) {
            fact_[i] = fact_[i - 1] * i;
        }
        invfact_[n_] = fact_[n_].inv();
        for (int i = n_; i > n; i--) {
            invfact_[i - 1] = invfact_[i] * i;
            inv_[i] = invfact_[i] * fact_[i - 1];
        }
        n = n_;
    }

    T fact(int k) {
        if (k > n) {
            init(2 * k);
        }
        return fact_[k];
    }
    T invfact(int k) {
        if (k > n) {
            init(2 * k);
        }
        return invfact_[k];
    }
    T inv(int k) {
        if (k > n) {
            init(2 * k);
        }
        return inv_[k];
    }
    T binom(int n, int m) {
        if (n < m || m < 0) {
            return 0;
        }
        return fact(n) * invfact(m) * invfact(n - m);
    }
    T perm(int n, int m) {
        if (n < m || m < 0) {
            return 0;
        }
        return fact(n) * invfact(n - m);
    }
    T multicomb(int n, int m) {
        if (n < 0 || m < 0) {
            return 0;
        }
        if (n == 0) {
            return (m == 0);
        }
        return binom(n + m - 1, m);
    }
    T Catalan(int n) {
        if (n < 0) {
            return 0;
        }
        return binom(2 * n, n) * inv(n + 1);
    }
};