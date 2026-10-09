#define PROBLEM "https://judge.yosupo.jp/problem/inverse_matrix"
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
    auto [det, inv] = matrixInv(a);
    if (det == ModInt998244353(0)) {
        cout << -1 << '\n';
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) cout << inv[i][j] << (j + 1 == n ? '\n' : ' ');
    }
}
