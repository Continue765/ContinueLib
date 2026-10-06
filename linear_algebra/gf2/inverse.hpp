#pragma once
#include <common.hpp>

namespace gf2 {

template <typename U>
vector<U> inverse(int n, vector<U> a) {
    vector<U> b(n);
    for (int i = 0; i < n; i++) {
        b[i] = U{1} << i;
    }
    for (int j = 0; j < n; j++) {
        int p = j;
        while (p < n && !(a[p] >> j & U{1})) {
            p++;
        }
        if (p == n) {
            return {};
        }
        swap(a[p], a[j]);
        swap(b[p], b[j]);
        for (int i = 0; i < n; i++) {
            if (i != j && (a[i] >> j & U{1})) {
                a[i] ^= a[j];
                b[i] ^= b[j];
            }
        }
    }
    return b;
}

}