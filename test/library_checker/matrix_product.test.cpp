#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product"
#include <common.hpp>
#include "number_theory/exgcd.hpp"
#include "mod/modint.hpp"
#include "linear_algebra/matrix.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    Matrix<ModInt998244353> a(n, m), b(m, k);
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> a[i][j];
    for (int i = 0; i < m; ++i) for (int j = 0; j < k; ++j) cin >> b[i][j];
    Matrix<ModInt998244353> c = a * b;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) cout << c[i][j] << (j + 1 == k ? '\n' : ' ');
    }
}
