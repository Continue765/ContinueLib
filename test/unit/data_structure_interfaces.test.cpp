#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <algebra/monoid.hpp>
#include <data_structure/dsu.hpp>
#include <data_structure/fenwick/fenwick_2d.hpp>
#include <data_structure/fenwick/fenwick.hpp>
#include <data_structure/binary_trie.hpp>
#include <data_structure/binary_lifting.hpp>
#include <data_structure/cartesian_tree.hpp>

void dsuTest(mt19937& rng) {
    for (int n = 1; n <= 40; n++) {
        DSU ds(n);
        vector<int> label(n);
        iota(label.begin(), label.end(), 0);
        for (int q = 0; q < 100; q++) {
            int u = rng() % n, v = rng() % n;
            bool merged = label[u] != label[v];
            assert(ds.merge(u, v) == merged);
            int old = label[v], to = label[u];
            for (auto& x : label) if (x == old) x = to;
            assert(!ds.merge(u, v));
            for (int x = 0; x < n; x++) {
                assert(ds.size(x) == count(label.begin(), label.end(), label[x]));
                assert(ds.same(u, x) == (label[u] == label[x]));
            }
        }
    }
}

void fenwickTest(mt19937& rng) {
    for (int h = 1; h <= 7; h++) for (int w = 1; w <= 7; w++) {
        vector<vector<i64>> a(h, vector<i64>(w));
        for (auto& row : a) for (auto& x : row) x = int(rng() % 101) - 50;
        Fenwick2D<AddMono<i64>> ds(a);
        for (int q = 0; q < 20; q++) {
            int x = rng() % h, y = rng() % w;
            i64 v = int(rng() % 21) - 10;
            a[x][y] += v;
            ds.add(x, y, v);
            for (int l = 0; l <= h; l++) for (int r = l; r <= h; r++) {
                for (int b = 0; b <= w; b++) for (int t = b; t <= w; t++) {
                    i64 sum = 0;
                    for (int i = l; i < r; i++) for (int j = b; j < t; j++) sum += a[i][j];
                    assert(ds.query(l, r, b, t) == sum);
                }
            }
        }
    }
    for (int n = 1; n <= 40; n++) {
        vector<int> a(n);
        Fenwick<AddMono<int>> ds(a);
        for (int q = 0; q < 100; q++) {
            int p = rng() % n, v = rng() % 5;
            ds.add(p, v); a[p] += v;
            int total = accumulate(a.begin(), a.end(), 0);
            for (int k = 0; k <= total; k++) {
                int pos = 0, remaining = k;
                while (pos < n && remaining >= a[pos]) remaining -= a[pos++];
                assert(ds.kth(k) == pos);
            }
        }
    }
}

void trieTest(mt19937& rng) {
    BinaryTrie ds(32 * 2002);
    multiset<int> values;
    for (int q = 0; q < 2000; q++) {
        if (values.empty() || rng() % 2) {
            int x = rng() & 0x7fffffff;
            if (q % 3 == 0) x = 7;
            ds.insert(x); values.insert(x);
        } else {
            auto it = next(values.begin(), rng() % values.size());
            ds.erase(*it); values.erase(it);
        }
        if (!values.empty()) {
            int x = rng() & 0x7fffffff, expected = 0;
            for (int v : values) expected = max(expected, x ^ v);
            assert(ds.query(x) == expected);
        }
    }
    while (!values.empty()) { ds.erase(*values.begin()); values.erase(values.begin()); }
    ds.insert(0);
    assert(ds.query(12345) == 12345);
}

struct Concat {
    using Type = string;
    static Type e() { return {}; }
    static Type op(const Type& a, const Type& b) { return a + b; }
};

void liftingTest(mt19937& rng) {
    for (int n = 1; n <= 40; n++) {
        BinaryLifting<Concat> ds(n);
        vector<int> nxt(n);
        vector<string> value(n);
        for (int i = 0; i < n; i++) {
            nxt[i] = int(rng() % (n + 1)) - 1;
            value[i] = char('a' + i % 26);
            ds.add(i, nxt[i], value[i]);
        }
        ds.build();
        for (int u = 0; u < n; u++) for (int k = 0; k < (1 << (ds.logn + 1)); k++) {
            int v = u;
            string expected;
            for (int j = 0; j < k && v != -1; j++) { expected += value[v]; v = nxt[v]; }
            assert(ds.jump(u, k) == v);
            assert(ds.query(u, k) == make_pair(v, expected));
        }
    }
}

template <bool isMin>
void cartesianTest(mt19937& rng) {
    for (int n = 0; n <= 60; n++) for (int type = 0; type < 4; type++) {
        vector<int> a(n);
        for (int i = 0; i < n; i++) a[i] = type == 0 ? i : type == 1 ? -i : type == 2 ? 1 : rng() % 10;
        CartesianTree<int, isMin> ds(a);
        auto solve = [&](auto&& self, int l, int r, int parent) -> int {
            if (l == r) return -1;
            int u = l;
            for (int i = l + 1; i < r; i++) if (isMin ? a[i] < a[u] : a[i] > a[u]) u = i;
            assert(ds.p[u] == parent && ds.range[u] == make_pair(l, r));
            assert(ds.L[u] == self(self, l, u, u));
            assert(ds.R[u] == self(self, u + 1, r, u));
            return u;
        };
        assert(ds.root == solve(solve, 0, n, -1));
    }
}

int main() {
    mt19937 rng(382781);
    dsuTest(rng);
    fenwickTest(rng);
    trieTest(rng);
    liftingTest(rng);
    cartesianTest<true>(rng);
    cartesianTest<false>(rng);
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
