#pragma once
#include <common.hpp>
#include <linear_algebra/matrix.hpp>

template <typename T>
pair<vector<int>, T> gauss(Matrix<T>& a) {
    vector<int> pivot;
    T prod = T{1};
    int r = 0;
    for (int j = 0; j < a.m && r < a.n; j++) {
        int p = r;
        while (p < a.n && a[p][j] == T{0}) {
            p++;
        }
        if (p == a.n) {
            continue;
        }
        if (p != r) {
            swap(a[p], a[r]);
            prod = -prod;
        }
        T x = a[r][j];
        prod *= x;
        pivot.push_back(j);
        for (int i = r + 1; i < a.n; i++) {
            if (a[i][j] == T{0}) {
                continue;
            }
            T c = a[i][j] / x;
            for (int k = j; k < a.m; k++) {
                a[i][k] -= c * a[r][k];
            }
        }
        r++;
    }
    return {pivot, prod};
}