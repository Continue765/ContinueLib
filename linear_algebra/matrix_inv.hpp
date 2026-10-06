#pragma once
#include <common.hpp>
#include <linear_algebra/matrix.hpp>

template <typename T>
pair<bool, Matrix<T>> matrixInv(Matrix<T> a) {
    if (a.n != a.m) {
        return {false, {}};
    }

    int n = a.n;
    Matrix<T> b(n, 2 * n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            b[i][j] = a[i][j];
        }
        b[i][n + i] = T{1};
    }

    for (int col = 0; col < n; col++) {
        int p = col;
        while (p < n && b[p][col] == T{0}) {
            p++;
        }
        if (p == n) {
            return {false, {}};
        }

        swap(b[p], b[col]);

        T x = b[col][col];
        for (int j = 0; j < 2 * n; j++) {
            b[col][j] /= x;
        }

        for (int i = 0; i < n; i++) {
            if (i == col || b[i][col] == T{0}) {
                continue;
            }

            T c = b[i][col];
            for (int j = 0; j < 2 * n; j++) {
                b[i][j] -= c * b[col][j];
            }
        }
    }

    Matrix<T> res(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] = b[i][n + j];
        }
    }

    return {true, res};
}