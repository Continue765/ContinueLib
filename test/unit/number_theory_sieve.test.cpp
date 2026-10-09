#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "number_theory/sieve.hpp"

void test() {
    sieve(1);
    assert(primes.empty() && minp.size() == 2);
    sieve(100);
    vector<int> expected = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47,
        53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    assert(primes == expected);
    for (int n = 2; n <= 100; n++) {
        int p = minp[n];
        assert(2 <= p && n % p == 0);
        for (int d = 2; d < p; d++) assert(n % d != 0);
    }
    sieve(12);
    assert(primes == vector<int>({2, 3, 5, 7, 11}));
}

int main() {
    test();
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
