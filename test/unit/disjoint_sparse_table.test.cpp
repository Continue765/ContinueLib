#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <data_structure/disjoint_spase_table.hpp>
#include <algebra/monoid.hpp>

struct Concat {
    using Type = string;
    static Type op(const Type& a, const Type& b) { return a + b; }
};

int main() {
    mt19937 rng(71925);
    for (int n = 1; n <= 70; n++) {
        vector<i64> a(n);
        vector<string> b(n);
        for (int i = 0; i < n; i++) {
            a[i] = int(rng() % 101) - 50;
            b[i] = string(1 + rng() % 3, char('a' + rng() % 26));
        }
        DisjointSparseTable<AddMono<i64>> sum(a);
        DisjointSparseTable<Concat> concat(b);
        for (int l = 0; l < n; l++) {
            i64 s = 0;
            string t;
            for (int r = l + 1; r <= n; r++) {
                s += a[r - 1];
                t += b[r - 1];
                assert(sum.query(l, r) == s);
                assert(concat.query(l, r) == t);
            }
        }
    }
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
