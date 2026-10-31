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
    for (i64 a = 1; a <= 30; ++a) for (i64 b = 1; b <= 30; ++b) {
        i64 d = exgcd(a, b, x, y);
        assert(d == gcd(a, b) && a * x + b * y == d);
        for (i64 c = -20; c <= 20; ++c) {
            bool ok = solveLinear(a, b, c, x, y);
            assert(ok == (c % d == 0));
            if (ok) assert(a * x + b * y == c);
        }
        i64 inverse = inv(a, b);
        if (d == 1) assert((a * inverse) % b == 1 % b);
        else assert(inverse == -1);
        for (i64 c = 0; c < b; ++c) {
            auto [solution, period] = solveMod(a, c, b);
            vector<i64> roots;
            for (i64 value = 0; value < b; ++value) {
                if ((a * value + c) % b == 0) roots.push_back(value);
            }
            if (roots.empty()) assert(solution == -1 && period == -1);
            else {
                assert(period == b / d && solution == roots[0]);
                for (int i = 0; i < int(roots.size()); ++i) assert(roots[i] == solution + i * period);
            }
        }
    }
}

int main() {
    test();
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
