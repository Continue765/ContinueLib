#pragma once
#include <common.hpp>

namespace gf2 {

template <typename U>
vector<U> transpose(int n, int m, const vector<U>& a) {
    vector<U> b(m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i] >> j & U{1}) {
                b[j] |= U{1} << i;
            }
        }
    }
    return b;
}

}