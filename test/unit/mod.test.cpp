#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "mod/all_inverse.hpp"
#include "mod/barrett.hpp"
#include "mod/calc.hpp"
#include "mod/modint.hpp"
#include "mod/modint_short.hpp"

void test() {
    Barrett bt(1000000007);
    assert(bt.mod() == 1000000007);
    mt19937_64 rng(918273645);
    for (int i = 0; i < 10000; i++) {
        uint32_t a = rng() % bt.mod();
        uint32_t b = rng() % bt.mod();
        assert(bt.multiply(a, b) == static_cast<uint64_t>(a) * b % bt.mod());
    }
    using M = ModInt998244353;
    assert(M(-1).value() == 998244352);
    assert(M(998244354).value() == 1);
    assert((M(7) + M(9)).value() == 16);
    assert((M(3) - M(8)).value() == 998244348);
    assert((M(123456) * M(789012)).value() == 123456ULL * 789012 % M::mod());
    assert((M(3) / M(2) * M(2)).value() == 3);
    assert(M(1).inverse() == M(1));
    M x = M::mod() - 1;
    ++x;
    assert(x == M(0));
    --x;
    assert(x == M::mod() - 1);
    stringstream ss("-4");
    M y;
    ss >> y;
    assert(y == M(-4));
    vector<M> vals = {2, 3, 5};
    auto invs = allInverse(vals);
    for (int i = 0; i < 3; i++) assert(vals[i] * invs[i] == M(1));
    assert(allInverse(vector<M>{}).empty());
    using D = ModInt<DynamicMod<17>>;
    DynamicMod<17>::setMod(101);
    assert((D(37) * D(44)).value() == 37 * 44 % 101);
    DynamicMod<17>::setMod(103);
    assert((D(37) * D(44)).value() == 37 * 44 % 103);
    assert(mul(123456789, 987654321, 1000000007) == 123456789LL * 987654321 % 1000000007);
    assert(power(2LL, 10LL, 1000LL) == 24);
    assert(power(3, 5) == 243);
    assert(Fp(-1).v == P - 1);
    assert((Fp(3) / Fp(2) * Fp(2)).v == 3);
}

int main() {
    test();
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
