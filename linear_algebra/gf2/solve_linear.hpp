#pragma once
#include <common.hpp>
#include <linear_algebra/gf2/transpose.hpp>

namespace gf2 {

template <unsigned_integral U>
vector<U> solveLinear(int n, int m, vector<U> a, U b) {
    vector<U> mat(m);
    U rhs = 0;
    for (int i = 0; i < n; i++) {
        U x = a[i], c = b >> i & 1;
        for (int j = m - 1; j >= 0; j--) {
            if ((x ^ mat[j]) < x) {
                x ^= mat[j];
                c ^= rhs >> j & 1;
            }
        }
        if (!x) {
            if (c) {
                return {};
            }
            continue;
        }
        int k = bit_width(x) - 1;
        for (int j = k; j < m; j++) {
            if ((mat[j] ^ x) < mat[j]) {
                mat[j] ^= x;
                rhs ^= c << j;
            }
        }
        mat[k] = x;
        rhs |= c << k;
    }
    vector<U> res{rhs};
    mat = transpose(m, m, mat);
    for (int j = 0; j < m; j++) {
        if (!(mat[j] >> j & 1)) {
            res.push_back(mat[j] | (U{1} << j));
        }
    }
    return res;
}

}