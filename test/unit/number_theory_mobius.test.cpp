#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "number_theory/mobius.hpp"

void test() {
    sieve(1);
    assert(mu == vector<int>({0, 1}));
    sieve(100);
    for (int n = 1; n <= 100; n++) {
        int squareFactor = 0;
        int sign = 1;
        int x = n;
        for (int p = 2; p * p <= x; p++) {
            if (x % p == 0) {
                x /= p;
                if (x % p == 0) squareFactor = 1;
                while (x % p == 0) x /= p;
                sign = -sign;
            }
        }
        if (x > 1) sign = -sign;
        assert(mu[n] == (squareFactor ? 0 : sign));
    }
    sieve(12);
    assert(mu[1] == 1 && mu[2] == -1 && mu[4] == 0 && mu[11] == -1);
}

int main() {
    test();
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
