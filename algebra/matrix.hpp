template <typename T>
struct Matrix {
    int n, m;
    vector<vector<T>> a;

    Matrix() {}
    Matrix(int n_, int m_, T v = T{}) : n(n_), m(m_), a(n, vector<T>(m, v)) {}
    Matrix(int n_) : Matrix(n_, n_) {
        for (int i = 0; i < n; i++) {
            a[i][i] = 1;
        }
    }

    vector<T>& operator[](int i) { return a[i]; }
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
    Matrix<T> res(a.n);
    for (; b > 0; b >>= 1) {
        if (b & 1) {
            res *= a;
        }
        a *= a;
    }
    return res;
}