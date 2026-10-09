#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "combinatorics/ie.hpp"
#include "combinatorics/zeta.hpp"

void test() {
    vector<int> exact = ieExact<int>(3, [](int mask) { return 1 << (3 - popcount(static_cast<unsigned>(mask))); });
    assert(exact == vector<int>({1, 3, 3, 1}));
    assert(ieLeast<int>(3, [](int mask) { return 1 << (3 - popcount(static_cast<unsigned>(mask))); }) == vector<int>({8, 7, 4, 1}));
    assert(ieMost<int>(3, [](int mask) { return 1 << (3 - popcount(static_cast<unsigned>(mask))); }) == vector<int>({1, 4, 7, 8}));
    assert(ie<int>(3, [](int mask) { return 1 << (3 - popcount(static_cast<unsigned>(mask))); }) == 7);
    assert(ieComp<int>(3, [](int mask) { return 1 << (3 - popcount(static_cast<unsigned>(mask))); }) == 1);

    vector<int> f = {1, 2, 3, 4};
    auto originalF = f;
    subsetZeta(f);
    assert(f == vector<int>({1, 3, 4, 10}));
    subsetMobius(f);
    assert(f == originalF);
    supersetZeta(f);
    assert(f == vector<int>({10, 6, 7, 4}));
    supersetMobius(f);
    assert(f == originalF);
}

int main() {
    test();
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
