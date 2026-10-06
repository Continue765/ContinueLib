#pragma once
#include <common.hpp>

struct Basis {
    array<i64, 64> p{};

    int size() {
        int r = 0;
        for (int i = 0; i < 64; i++) {
            r += p[i] != 0;
        }
        return r;
    }

    bool insert(i64 x) {
        for (int i = 63; i >= 0; i--) {
            if (!(x >> i & 1)) {
                continue;
            }
            if (!p[i]) {
                p[i] = x;
                return true;
            }
            x ^= p[i];
        }
        return false;
    }

    bool check(i64 x) {
        for (int i = 63; i >= 0; i--) {
            if (x >> i & 1) {
                x ^= p[i];
            }
        }
        return x == 0;
    }

    i64 getMax(i64 start = 0) {
        i64 res = start;
        for (int i = 63; i >= 0; i--) {
            if ((res ^ p[i]) > res) {
                res ^= p[i];
            }
        }
        return res;
    }

    i64 getMin() {
        for (int i = 0; i < 64; i++) {
            if (p[i]) {
                return p[i];
            }
        }
        return 0;
    }

    void gauss() {
        for (int i = 63; i >= 0; i--) {
            if (!p[i]) {
                continue;
            }
            for (int j = i - 1; j >= 0; j--) {
                if (p[i] >> j & 1) {
                    p[i] ^= p[j];
                }
            }
        }
    }

    i64 kth(i64 k) {
        vector<i64> b;
        for (int i = 0; i < 64; i++) {
            if (p[i]) {
                b.push_back(p[i]);
            }
        }
        int r = b.size();
        if (k < 1 || (r < 63 && k > (1LL << r))) {
            return -1;
        }
        k--;
        i64 res = 0;
        for (int i = 0; i < r; i++) {
            if (k >> i & 1) {
                res ^= b[i];
            }
        }
        return res;
    }
};
