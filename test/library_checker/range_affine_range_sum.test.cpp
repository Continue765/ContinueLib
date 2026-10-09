#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"
#include <common.hpp>
#include "data_structure/segment_tree/lazy_segment_tree.hpp"

struct Mod {
    static constexpr long long mod = 998244353;
    long long v;
    Mod(long long x = 0) : v((x % mod + mod) % mod) {}
    Mod& operator+=(Mod x) { v = (v + x.v) % mod; return *this; }
    Mod& operator-=(Mod x) { v = (v - x.v + mod) % mod; return *this; }
    Mod& operator*=(Mod x) { v = v * x.v % mod; return *this; }
    friend Mod operator+(Mod a, Mod b) { return a += b; }
    friend Mod operator-(Mod a, Mod b) { return a -= b; }
    friend Mod operator*(Mod a, Mod b) { return a *= b; }
    friend ostream& operator<<(ostream& out, Mod x) { return out << x.v; }
    friend istream& operator>>(istream& in, Mod& x) { long long v; in >> v; x = Mod(v); return in; }
};

struct SumMono {
    using Type = Mod;
    static Type e() { return 0; }
    static Type op(Type a, Type b) { return a + b; }
};

struct AffineTag {
    using Type = pair<Mod, Mod>;
    static Type e() { return {1, 0}; }
    static Type op(const Type& old, const Type& next) {
        return {next.first * old.first, next.first * old.second + next.second};
    }
};

struct SumAffine {
    using Mono = SumMono;
    using Tag = AffineTag;
    using X = Mono::Type;
    using Y = Tag::Type;
    static X act(X sum, const Y& f, int len) { return f.first * sum + f.second * len; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<Mod> a(n);
    for (auto& x : a) cin >> x;
    LazySegmentTree<SumAffine> seg(a);
    while (q--) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 0) {
            Mod b, c;
            cin >> b >> c;
            seg.rangeApply(l, r, {b, c});
        } else {
            cout << seg.rangeQuery(l, r) << '\n';
        }
    }
}
