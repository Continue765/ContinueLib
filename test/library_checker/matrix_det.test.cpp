#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"
#include <common.hpp>
#include "number_theory/exgcd.hpp"
#include "mod/modint.hpp"
#include "linear_algebra/gauss.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    Matrix<ModInt998244353> a(n, n);
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> a[i][j];
    cout << determinant(a) << '\n';
}
