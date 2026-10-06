#pragma once
#include <common.hpp>

struct Basis {
    array<u64, 64> p{};
    bool norm = false;

    int size() {
        int r = 0;
        for (int i = 0; i < 64; i++) {
            r += p[i] != 0;
        }
        return r;
    }

    bool insert(u64 x) {
        for (int i = 63; i >= 0; i--) {
            if (!(x >> i & 1)) {
                continue;
            }
            if (!p[i]) {
                p[i] = x;
                norm = false;
                return true;
            }
            x ^= p[i];
        }
        return false;
    }

    bool contain(u64 x) {
        for (int i = 63; i >= 0; i--) {
            if (x >> i & 1) {
                x ^= p[i];
            }
        }
        return x == 0;
    }

    u64 getMax(u64 x = 0) {
        for (int i = 63; i >= 0; i--) {
            if ((x ^ p[i]) > x) {
                x ^= p[i];
            }
        }
        return x;
    }

    u64 getMin(u64 x = 0) {
        for (int i = 63; i >= 0; i--) {
            if ((x ^ p[i]) < x) {
                x ^= p[i];
            }
        }
        return x;
    }

    void normalize() {
        if (norm == true) {
            return;
        }
        norm = true;
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

    u64 kth(u64 k) {
        normalize();
        vector<u64> b;
        for (int i = 0; i < 64; i++) {
            if (p[i]) {
                b.push_back(p[i]);
            }
        }
        int r = b.size();
        if (r < 64) {
            if (k < (1LL << r)) {
                return -1;
            }
        }
        u64 res = 0;
        for (int i = 0; i < r; i++) {
            if (k >> i & 1) {
                res ^= b[i];
            }
        }
        return res;
    }
};
