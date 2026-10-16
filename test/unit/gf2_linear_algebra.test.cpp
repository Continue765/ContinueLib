#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "linear_algebra/gf2/basis.hpp"
#include "linear_algebra/gf2/inverse.hpp"
#include "linear_algebra/gf2/solve_linear.hpp"

void checkSolve(int n, int m, vector<u64> rows, u64 rhs) {
    auto actual = gf2::solveLinear(n, m, rows, rhs);
    set<u64> expected;
    for (u64 x = 0; x < (1ULL << m); ++x) {
        bool valid = true;
        for (int i = 0; i < n; ++i) {
            if (__builtin_parityll(rows[i] & x) != ((rhs >> i) & 1)) valid = false;
        }
        if (valid) expected.insert(x);
    }
    if (expected.empty()) {
        assert(actual.empty());
        return;
    }
    assert(!actual.empty());
    set<u64> generated;
    for (int mask = 0; mask < (1 << (actual.size() - 1)); ++mask) {
        u64 x = actual[0];
        for (int j = 1; j < (int)actual.size(); ++j) {
            if (mask >> (j - 1) & 1) x ^= actual[j];
        }
        generated.insert(x);
    }
    assert(generated == expected);
}

int main() {
    vector<u64> rows{0b10101, 0b01110, 0b11000};
    auto cols = gf2::transpose(3, 5, rows);
    assert(cols == vector<u64>({0b001, 0b010, 0b011, 0b110, 0b101}));
    assert(gf2::transpose(5, 3, cols) == rows);

    vector<u64> matrix{0b011, 0b110, 0b100};
    auto inverse = gf2::inverse(3, matrix);
    assert(inverse.size() == 3);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            auto inverseCols = gf2::transpose(3, 3, inverse);
            bool dot = __builtin_parityll(matrix[i] & inverseCols[j]);
            assert(dot == (i == j));
        }
    }
    assert(gf2::inverse(2, vector<u64>{0b01, 0b01}).empty());

    checkSolve(3, 4, {0b0011, 0b0110, 0b1100}, 0b101);
    checkSolve(4, 3, {0b011, 0b110, 0b101, 0b001}, 0b0011);
    checkSolve(3, 4, {0b0011, 0b0110, 0b1100}, 0b111);
    checkSolve(0, 4, {}, 0);

    Basis basis;
    vector<u64> values{0b10110, 0b01101, 0b11000, 0b00101, 0b10010};
    set<u64> span{0};
    for (u64 x : values) {
        set<u64> next = span;
        for (u64 y : span) next.insert(y ^ x);
        span.swap(next);
        basis.insert(x);
    }
    assert(basis.size() == (int)log2(span.size()));
    for (u64 x = 0; x < 64; ++x) assert(basis.contain(x) == span.contains(x));
    assert(basis.getMax() == *span.rbegin());
    assert(basis.getMin() == *span.begin());
    u64 index = 0;
    for (u64 x : span) assert(basis.kth(index++) == x);
    assert(basis.kth(index) == numeric_limits<u64>::max());
    assert(!basis.insert(0));

    for (int n : {1, 31, 32, 63, 64}) {
        vector<u64> identity(n);
        for (int i = 0; i < n; i++) identity[i] = u64{1} << i;
        assert(gf2::transpose(n, n, identity) == identity);
        assert(gf2::inverse(n, identity) == identity);
        u64 mask = n == 64 ? ~u64{0} : (u64{1} << n) - 1;
        assert(gf2::solveLinear(n, n, identity, mask) == vector<u64>{mask});
    }
    Basis full;
    for (int i = 63; i >= 0; i--) assert(full.insert(u64{1} << i));
    assert(full.size() == 64 && full.getMax() == ~u64{0});
    for (u64 x : {u64{0}, u64{1}, u64{1} << 63, ~u64{0}}) {
        assert(full.contain(x) && full.kth(x) == x);
    }
    mt19937_64 rng(765);
    for (int n : {31, 32, 63, 64}) {
        vector<u64> mat(n);
        for (int i = 0; i < n; i++) mat[i] = u64{1} << i;
        for (int i = 0; i < 1000; i++) {
            int u = rng() % n, v = rng() % n;
            if (u != v) mat[u] ^= mat[v];
        }
        auto inv = gf2::inverse(n, mat);
        assert(int(inv.size()) == n);
        auto cols = gf2::transpose(n, n, inv);
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
            assert(__builtin_parityll(mat[i] & cols[j]) == (i == j));
        }
        u64 rhs = rng() & (n == 64 ? ~u64{0} : (u64{1} << n) - 1);
        auto sol = gf2::solveLinear(n, n, mat, rhs);
        assert(sol.size() == 1);
        for (int i = 0; i < n; i++) {
            assert(__builtin_parityll(mat[i] & sol[0]) == ((rhs >> i) & 1));
        }
        mat.back() = mat.front();
        assert(gf2::inverse(n, mat).empty());
    }
    for (int it = 0; it < 500; it++) {
        int n = rng() % 7, m = rng() % 7;
        vector<u64> a(n);
        for (auto& x : a) x = rng() & ((u64{1} << m) - 1);
        checkSolve(n, m, a, rng() & ((u64{1} << n) - 1));
    }
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
