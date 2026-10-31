#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <algebra/act.hpp>
#include <algebra/power.hpp>
#include <data_structure/segment_tree/lazy_segment_tree.hpp>
#include <mod/all_inverse.hpp>
#include <mod/calc.hpp>
#include <mod/modint.hpp>
#include <mod/modint_short.hpp>

template <typename Act>
void actionTest(mt19937& rng) {
    using Mono = typename Act::Mono;
    using Tag = typename Act::Tag;
    for (int n = 1; n <= 31; n++) {
        vector<i64> a(n);
        for (auto& x : a) x = int(rng() % 21) - 10;
        LazySegmentTree<Act> ds(a);
        for (int q = 0; q < 100; q++) {
            int l = rng() % (n + 1), r = rng() % (n + 1);
            if (l > r) swap(l, r);
            i64 tag = is_same_v<Tag, MulMono<i64>> ? int(rng() % 3) - 1 : int(rng() % 11) - 5;
            ds.apply(l, r, tag);
            for (int i = l; i < r; i++) {
                if constexpr (is_same_v<Tag, MulMono<i64>>) a[i] *= tag;
                else a[i] += tag;
            }
            if (q % 4 == 0) {
                int p = rng() % n;
                a[p] = int(rng() % 21) - 10;
                ds.modify(p, a[p]);
            }
            int x = rng() % (n + 1), y = rng() % (n + 1);
            if (x > y) swap(x, y);
            i64 expected = Mono::e();
            for (int i = x; i < y; i++) {
                if constexpr (is_same_v<Mono, AddMono<i64>>) expected += a[i];
                else if constexpr (is_same_v<Mono, MinMono<i64>>) expected = min(expected, a[i]);
                else expected = max(expected, a[i]);
            }
            assert(ds.query(x, y) == expected);
        }
    }
}

template <typename Mint>
void modularTest(mt19937_64& rng, i64 mod) {
    auto norm = [&](i64 x) { return (x % mod + mod) % mod; };
    auto value = [&](Mint x) {
        stringstream ss;
        ostream& out = ss;
        out << x;
        return stoll(ss.str());
    };
    for (int q = 0; q < 2000; q++) {
        i64 x = i64(rng() % (4 * mod + 1)) - 2 * mod;
        i64 y = i64(rng() % (4 * mod + 1)) - 2 * mod;
        Mint a(x), b(y);
        i64 u = norm(x), v = norm(y);
        assert(value(a) == u && value(b) == v);
        assert(value(a + b) == norm(u + v));
        assert(value(a - b) == norm(u - v));
        assert(value(a * b) == i128(u) * v % mod);
        assert(value(-a) == norm(-u));
        assert((a == b) == (u == v));
        stringstream in(to_string(u));
        Mint parsed;
        in >> parsed;
        assert(parsed == a);
        if (gcd(v, mod) == 1) {
            Mint quotient = a / b;
            assert(quotient * b == a);
        }
    }
}

void algebraTest() {
    assert(MinMono<int>::e() == inf<int> && MaxMono<int>::e() == -inf<int>);
    assert(GcdMono<int>::e() == 0 && LcmMono<int>::e() == 1 && XorMono<int>::e() == 0);
    assert(GcdMono<int>::pow(12, 0) == 0 && GcdMono<int>::pow(12, 9) == 12);
    assert(LcmMono<int>::pow(12, 0) == 1 && LcmMono<int>::pow(12, 9) == 12);
    assert(XorMono<int>::inv(7) == 7 && XorMono<int>::power(7, 3) == 7);
    assert(MulMono<double>::inv(2) == 0.5);
    assert(AddMono<i64>::from(-17) == -17 && MulMono<i64>::from(-17) == -17);
    assert(MinMono<i64>::from(-17) == -17 && MaxMono<i64>::from(-17) == -17);
    assert(GcdMono<i64>::from(17) == 17 && LcmMono<i64>::from(17) == 17);
    assert(power<MulMono<i64>>(7, 0) == 1);
    assert(power<AddMono<i64>>(7, 0) == 0);
    assert(power<XorMono<int>>(7, 0) == 0 && power<XorMono<int>>(7, 3) == 7);
    assert(power(7LL, 0LL, 1LL) == 0 && power(7, 0) == 1);
}

int main() {
    mt19937 rng(182783);
    actionTest<SumMul<i64>>(rng);
    actionTest<MinAdd<i64>>(rng);
    actionTest<MaxAdd<i64>>(rng);
    algebraTest();
    mt19937_64 rng64(983471);
    modularTest<ModInt998244353>(rng64, 998244353);
    modularTest<Fp>(rng64, P);
    modularTest<ModInt<StaticMod64<1000000007ULL>>>(rng64, 1000000007);
    DynamicMod<781>::setMod(12);
    modularTest<ModInt<DynamicMod<781>>>(rng64, 12);
    DynamicMod<781>::setMod(101);
    modularTest<ModInt<DynamicMod<781>>>(rng64, 101);
    using M = ModInt998244353;
    for (int n : {0, 1, 2, 17, 100}) {
        vector<M> a(n);
        for (auto& x : a) x = 1 + rng() % (M::mod() - 1);
        auto inverse = allInverse(a);
        assert(inverse.size() == a.size());
        for (int i = 0; i < n; i++) assert(a[i] * inverse[i] == M(1));
    }
    M x = M::mod() - 1;
    assert(x++ == M(M::mod() - 1) && x == M(0));
    assert(x-- == M(0) && x == M(M::mod() - 1));
    assert(+x == x && static_cast<i64>(x) == M::mod() - 1);
    assert(M(2) < M(3) && M(3) > M(2));
    for (int q = 0; q < 2000; q++) {
        i64 mod = 1 + rng64() % 1000000000000ULL;
        i64 a = rng64() % mod, b = rng64() % mod;
        assert(mul(a, b, mod) == i128(a) * b % mod);
        int exponent = rng() % 30;
        i64 expected = 1 % mod;
        for (int i = 0; i < exponent; i++) expected = i128(expected) * a % mod;
        assert(power(a, i64(exponent), mod) == expected);
    }
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
