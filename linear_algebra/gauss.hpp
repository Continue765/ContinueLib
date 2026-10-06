#pragma once
#include <common.hpp>
#include <linear_algebra/matrix.hpp>

template <typename T>
pair<vector<int>, T> eliminate(Matrix<T>& A, int lim, bool full) {
    // full == true -> RREF
    // full == false -> REF
    vector<int> pivot;
    T prod = T{1};
    int r = 0;
    for (int j = 0; j < lim && r < A.n; j++) {
        int p = r;
        while (p < A.n && A[p][j] == T{0}) {
            p++;
        }
        if (p == A.n) {
            continue;
        }
        if (p != r) {
            swap(A[p], A[r]);
            prod = -prod;
        }
        T x = A[r][j];
        prod *= x;
        pivot.push_back(j);
        T inv = T{1} / x;
        for (int k = j; k < A.m; k++) {
            A[r][k] *= inv;
        }
        for (int i = 0; i < A.n; i++) {
            if (i == r || (!full && i < r)) {
                continue;
            }
            T c = A[i][j];
            if (c == T{0}) {
                continue;
            }
            A[i][j] = T{0};
            for (int k = j + 1; k < A.m; k++) {
                A[i][k] -= c * A[r][k];
            }
        }
        r++;
    }
    return {pivot, prod};
}

template <typename T>
pair<vector<int>, T> gauss(Matrix<T>& A) {
    return eliminate(A, A.m, false);
}
template <typename T>
pair<vector<int>, T> gaussJordan(Matrix<T>& A, int lim) {
    return eliminate(A, lim, true);
}

template <typename T>
pair<T, Matrix<T>> matrixInv(const Matrix<T>& a) {
    if (a.n != a.m) {
        return {T{0}, {}};
    }
    int n = a.n;
    auto aug = augment(a, Matrix<T>::identity(n));
    auto [pivot, det] = gaussJordan(aug, n);
    if (pivot.size() < n) {
        return {T{0}, {}};
    }
    Matrix<T> inv(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inv[i][j] = aug[i][n + j];
        }
    }
    return {det, inv};
}

template <typename T>
int matrixRank(Matrix<T> a) {
    auto [pivot, prod] = gauss(a);
    return pivot.size();
}

template <typename T>
T determinant(Matrix<T> A) {
    assert(A.n == A.m);
    auto [pivot, det] = gauss(A);
    if (pivot.size() < A.n) {
        return T{0};
    }
    return det;
}

template <typename T>
vector<vector<T>> solveLinear(const Matrix<T>& A, const vector<T>& b) {
    int n = A.n;
    int m = A.m;
    auto aug = augment(A, b);
    auto [pivot, prod] = gaussJordan(aug, m);
    int r = pivot.size();
    for (int i = r; i < n; i++) {
        if (aug[i][m] != T{0}) {
            return {};
        }
    }
    vector<int> row(m, -1);
    for (int i = 0; i < r; i++) {
        row[pivot[i]] = i;
    }
    vector<vector<T>> sol(1, vector<T>(m));
    for (int j = 0; j < m; j++) {
        if (row[j] != -1) {
            sol[0][j] = aug[row[j]][m];
        }
    }
    for (int j = 0; j < m; j++) {
        if (row[j] != -1) {
            continue;
        }
        vector<T> x(m);
        x[j] = T{-1};
        for (int i = 0; i < r; i++) {
            x[pivot[i]] = aug[i][j];
        }
        sol.push_back(x);
    }
    return sol;
}