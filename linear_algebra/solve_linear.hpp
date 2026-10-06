#pragma once
#include <linear_algebra/matrix.hpp>

template <typename T>
vector<vector<T>> solveLinear(Matrix<T> a, vector<T> b) {
    int n = a.n, m = a.m;
    int r = 0;
    vector<int> pivot(m, -1);

    for (int j = 0; j < m && r < n; j++) {
        int p = r;
        while (p < n && a[p][j] == T{0}) {
            p++;
        }
        if (p == n) {
            continue;
        }
        swap(a[r], a[p]);
        swap(b[r], b[p]);
        T c = T{1} / a[r][j];
        for (auto& x : a[r]) {
            x *= c;
        }
        b[r] *= c;
        for (int i = 0; i < n; i++) {
            if (i == r || a[i][j] == T{0}) {
                continue;
            }
            T c = a[i][j];
            b[i] -= b[r] * c;
            for (int k = j; k < m; k++) {
                a[i][k] -= a[r][k] * c;
            }
        }
        pivot[j] = r++;
    }
    for (int i = r; i < n; i++) {
        if (b[i] != T{0}) {
            return {};
        }
    }
    vector<vector<T>> res(1, vector<T>(m));
    for (int j = 0; j < m; j++) {
        if (pivot[j] != -1) {
            res[0][j] = b[pivot[j]];
        }
    }
    for (int j = 0; j < m; j++) {
        if (pivot[j] != -1) {
            continue;
        }
        vector<T> x(m);
        x[j] = T{-1};
        for (int k = 0; k < j; k++) {
            if (pivot[k] != -1) {
                x[k] = a[pivot[k]][j];
            }
        }
        res.push_back(x);
    }

    return res;
}