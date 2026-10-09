#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "algebra/monoid.hpp"
#include "data_structure/fenwick/dual_fenwick.hpp"
#include "data_structure/fenwick/fenwick_2d.hpp"
#include "data_structure/fenwick/fenwick_range_add.hpp"

struct AdditiveGroup {
    using Type = long long;
    static Type e() { return 0; }
    static Type op(Type a, Type b) { return a + b; }
    static Type inv(Type a) { return -a; }
    static Type power(Type a, i64 k) { return a * k; }
};

int main() {
    vector<int> freq{1, 0, 2, 3, 1, 0, 2};
    Fenwick<AddMono<int>> fw(freq.size());
    for (int i = 0; i < (int)freq.size(); ++i) fw.add(i, freq[i]);
    for (int k = 0; k < accumulate(freq.begin(), freq.end(), 0); ++k) {
        int expected = 0, remain = k;
        while (remain >= freq[expected]) remain -= freq[expected++];
        assert(fw.kth(k) == expected);
    }
    for (int i = 0; i <= (int)freq.size(); ++i) {
        assert(fw.sum(i) == accumulate(freq.begin(), freq.begin() + i, 0));
    }

    Fenwick2D<AddMono<long long>> fw2(3, 4);
    long long grid[3][4]{};
    auto add2 = [&](int x, int y, long long v) {
        grid[x][y] += v;
        fw2.add(x, y, v);
    };
    add2(0, 0, 4);
    add2(0, 3, -2);
    add2(1, 2, 7);
    add2(2, 1, 5);
    add2(2, 3, 3);
    for (int x1 = 0; x1 <= 3; ++x1) {
        for (int x2 = x1; x2 <= 3; ++x2) {
            for (int y1 = 0; y1 <= 4; ++y1) {
                for (int y2 = y1; y2 <= 4; ++y2) {
                    long long expected = 0;
                    for (int i = x1; i < x2; ++i) {
                        for (int j = y1; j < y2; ++j) expected += grid[i][j];
                    }
                    assert(fw2.rangeSum(x1, x2, y1, y2) == expected);
                }
            }
        }
    }

    DualFenwick<AdditiveGroup> dual(6);
    vector<long long> values(6);
    auto rangeAdd = [&](int l, int r, long long v) {
        dual.add(l, r, v);
        for (int i = l; i < r; ++i) values[i] += v;
    };
    rangeAdd(0, 6, 3);
    rangeAdd(2, 5, -4);
    rangeAdd(4, 4, 100);
    for (int i = 0; i < 6; ++i) assert(dual.query(i) == values[i]);

    FenwickRangeAdd<AdditiveGroup> range(7);
    vector<long long> plain(7);
    auto rangeAddAndCheck = [&](int l, int r, long long v) {
        range.add(l, r, v);
        for (int i = l; i < r; ++i) plain[i] += v;
        for (int x = 0; x <= 7; ++x) {
            assert(range.sum(x) == accumulate(plain.begin(), plain.begin() + x, 0LL));
        }
    };
    rangeAddAndCheck(0, 7, 2);
    rangeAddAndCheck(1, 5, -3);
    rangeAddAndCheck(3, 3, 8);
    rangeAddAndCheck(6, 7, 4);

    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
