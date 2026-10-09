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
}

int main() {
    test();
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
