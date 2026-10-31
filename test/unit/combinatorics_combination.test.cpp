#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "mod/modint_short.hpp"
#include "combinatorics/combination.hpp"

void test() {
    Combination<Fp> c;
    assert(c.binom(0, 0) == 1);
    assert(c.binom(5, 2) == 10);
    assert(c.perm(5, 2) == 20);
    assert(c.multicomb(3, 2) == 6);
    assert(c.multicomb(0, 0) == 1 && c.multicomb(0, 3) == 0);
    assert(c.Catalan(4) == 14);
    assert(c.binom(4, 5) == 0 && c.binom(4, -1) == 0);
    assert(c.fact(0) == 1 && c.invfact(3) * c.fact(3) == 1);
    assert(c.inv(4) * 4 == 1);
    c.init(3);
    assert(c.fact(8) == 40320);
    vector<vector<Fp>> pascal(101, vector<Fp>(101));
    pascal[0][0] = 1;
    for (int n = 1; n <= 100; ++n) {
        pascal[n][0] = 1;
        for (int k = 1; k <= n; ++k) {
            pascal[n][k] = pascal[n - 1][k - 1] + pascal[n - 1][k];
        }
    }
    for (int n = 0; n <= 100; ++n) {
        for (int k = 0; k <= n; ++k) assert(c.binom(n, k) == pascal[n][k]);
    }
}

int main() {
    test();
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
