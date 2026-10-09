#define PROBLEM "https://judge.yosupo.jp/problem/primality_test"
#include <common.hpp>
#include "number_theory/miller_rabin.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        i64 n;
        cin >> n;
        cout << (isPrime(n) ? "Yes" : "No") << '\n';
    }
}
