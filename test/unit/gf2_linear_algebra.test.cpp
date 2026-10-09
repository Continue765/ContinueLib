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

    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
