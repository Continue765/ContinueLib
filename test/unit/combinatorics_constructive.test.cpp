#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "combinatorics/cantor.hpp"
#include "combinatorics/inversions.hpp"
#include "combinatorics/polyomino.hpp"

void test() {
    vector<int> p = {2, 0, 3, 1};
    auto code = toLehmer(p);
    assert(code == vector<int>({2, 0, 1, 0}));
    assert(fromLehmer(code) == p);
    assert(toRank(p) == 13);
    assert(fromRank(4, 13) == p);
    vector<int> empty;
    assert(toRank(empty) == 0 && fromRank(0, 0).empty());

    for (int n = 0; n <= 8; n++) {
        vector<i64> a(n), tmp(n);
        mt19937 rng(987654 + n);
        for (auto& x : a) x = rng() % 9 - 4;
        auto original = a;
        i64 brute = 0;
        for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) brute += original[i] > original[j];
        assert(invCount(a, 0, n, tmp) == brute);
        assert(is_sorted(a.begin(), a.end()));
    }

    set<Polyomino::Cell> cells = {{-2, 4}, {-1, 4}, {-1, 5}};
    Polyomino shape(cells);
    assert(normalize(shape).cells == set<Polyomino::Cell>({{0, 0}, {1, 0}, {1, 1}}));
    auto rotated = rotate(shape);
    assert(rotated.cells.size() == shape.cells.size());
    assert(rotate(rotate(rotate(rotate(shape)))).cells == normalize(shape).cells);
    assert(flip(flip(shape)).cells == normalize(shape).cells);
    assert(normalize(Polyomino()).cells.empty());
}

int main() {
    test();
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
