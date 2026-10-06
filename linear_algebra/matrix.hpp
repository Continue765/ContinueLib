#pragma once
#include <common.hpp>

template <typename T>
struct Matrix {
    int n, m;
    vector<vector<T>> a;

    Matrix() : n(0), m(0) {}
    Matrix(int n_, int m_, T v = T{}) : n(n_), m(m_), a(n, vector<T>(m, v)) {}
    Matrix(int n_) : Matrix(n_, n_) {}

    static Matrix identity(int n) {
        Matrix res(n);
        for (int i = 0; i < n; i++) {
            res[i][i] = T{1};
        }
        return res;
    }

    vector<T>& operator[](int i) {
        return a[i];
    }
    const vector<T>& operator[](int i) const {
        return a[i];
    }
};

template <typename T>
Matrix<T> operator*(const Matrix<T>& a, const Matrix<T>& b) {
    assert(a.m == b.n);
    Matrix<T> c(a.n, b.m);
    for (int i = 0; i < c.n; i++) {
        for (int k = 0; k < a.m; k++) {
            for (int j = 0; j < c.m; j++) {
                c.a[i][j] += a.a[i][k] * b.a[k][j];
            }
        }
    }
    return c;
}

template <typename T>
Matrix<T>& operator*=(Matrix<T>& a, const Matrix<T>& b) {
    return a = a * b;
}

template <typename T, integral U>
Matrix<T> power(Matrix<T> a, U b) {
    Matrix<T> res = Matrix<T>::identity(a.n);
    for (; b > 0; b >>= 1) {
        if (b & 1) {
            res *= a;
        }
        a *= a;
    }
    return res;
}

template <typename T>
Matrix<T> transpose(const Matrix<T>& a) {
    Matrix<T> res(a.m, a.n);
    for (int i = 0; i < a.n; i++) {
        for (int j = 0; j < a.m; j++) {
            res[j][i] = a[i][j];
        }
    }
    return res;
}

template <typename T>
Matrix<T> augment(const Matrix<T>& a, const Matrix<T>& b) {
    assert(a.n == b.n);
    Matrix<T> res(a.n, a.m + b.m);
    for (int i = 0; i < a.n; i++) {
        for (int j = 0; j < a.m; j++) {
            res[i][j] = a[i][j];
        }
        for (int j = 0; j < b.m; j++) {
            res[i][a.m + j] = b[i][j];
        }
    }
    return res;
}

template <typename T>
Matrix<T> augment(const Matrix<T>& a, const vector<T>& b) {
    assert(a.n == int(b.size()));
    Matrix<T> res(a.n, a.m + 1);
    for (int i = 0; i < a.n; i++) {
        for (int j = 0; j < a.m; j++) {
            res[i][j] = a[i][j];
        }
        res[i][a.m] = b[i];
    }
    return res;
}