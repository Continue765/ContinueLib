#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "number_theory/miller_rabin.hpp"

void test() {
    assert(!isPrime(-7) && !isPrime(0) && !isPrime(1));
    assert(isPrime(2) && isPrime(3) && !isPrime(4));
    for (i64 n = 0; n <= 10000; n++) {
        bool prime = n >= 2;
        for (i64 d = 2; d * d <= n; d++) prime &= n % d != 0;
        assert(isPrime(n) == prime);
    }
    assert(isPrime(2305843009213693951LL));
    assert(!isPrime(341550071728321LL));
}

int main() {
    test();
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
