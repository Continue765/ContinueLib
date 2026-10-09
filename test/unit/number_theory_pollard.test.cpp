#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "number_theory/pollard.hpp"
#include "number_theory/divisors.hpp"

void test() {
    assert(primeFactor(2) == 2);
    for (i64 n : {1LL, 2LL, 12LL, 97LL, 1000003LL, 1000003LL * 1000033LL,
            3LL * 3 * 3 * 1000003}) {
        auto factors = factorize(n);
        i64 product = 1;
        for (auto [p, e] : factors) {
            assert(isPrime(p) && e > 0);
            while (e--) product *= p;
        }
        assert(product == n);
        assert(is_sorted(factors.begin(), factors.end()));
        auto divisors = buildDivisors(factors);
        assert(divisors.size() == [&] { int count = 1; for (auto [p, e] : factors) count *= e + 1; return count; }());
        for (i64 d : divisors) assert(n % d == 0);
    }
    auto ds = buildDivisors({{2, 2}, {3, 1}});
    sort(ds.begin(), ds.end());
    assert(ds == vector<i64>({1, 2, 3, 4, 6, 12}));
}

int main() {
    test();
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
