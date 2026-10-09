#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_primes"
#include <common.hpp>
#include "number_theory/sieve.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, a, b;
    cin >> n >> a >> b;
    sieve(n);
    vector<int> selected;
    for (int i = b; i < static_cast<int>(primes.size()); i += a) selected.push_back(primes[i]);
    cout << primes.size() << ' ' << selected.size() << '\n';
    for (int i = 0; i < static_cast<int>(selected.size()); i++) cout << (i ? " " : "") << selected[i];
    cout << '\n';
}
