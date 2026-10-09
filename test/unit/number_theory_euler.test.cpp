#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "number_theory/euler.hpp"

void test() {
    sieve(1);
    assert(phi == vector<int>({0, 1}));
    sieve(100);
    for (int n = 1; n <= 100; n++) {
        int cnt = 0;
        for (int k = 1; k <= n; k++) cnt += gcd(k, n) == 1;
        assert(phi[n] == cnt);
        assert(Phi(n) == cnt);
    }
    sieve(12);
    assert(phi[1] == 1 && phi[8] == 4 && Phi(36) == 12);
}

int main() {
    test();
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
