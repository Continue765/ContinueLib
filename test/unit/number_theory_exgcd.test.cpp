#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "number_theory/exgcd.hpp"

void test() {
    i64 x, y;
    i64 g = exgcd(30, 18, x, y);
    assert(g == 6 && 30 * x + 18 * y == g);
    assert(inv(3, 11) == 4);
    assert(inv(6, 9) == -1);
    assert(solveLinear(6, 9, 3, x, y));
    assert(6 * x + 9 * y == 3);
    assert(!solveLinear(6, 9, 4, x, y));
    auto [root, period] = solveMod(6, 8, 14);
    assert(root == 1 && period == 7);
    tie(root, period) = solveMod(6, 7, 14);
    assert(root == -1 && period == -1);
    tie(root, period) = solveMod(0, 0, 13);
    assert(root == 0 && period == 1);
}

int main() {
    test();
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
