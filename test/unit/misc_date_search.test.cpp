#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "misc/binary_search.hpp"
#include "misc/date.hpp"

void test() {
    assert(firstTrue<i64>(-10, 11, [](i64 x) { return x >= 6; }) == 6);
    assert(lastTrue<i64>(-10, 11, [](i64 x) { return x <= 6; }) == 6);
    // 闭区间端点与单点区间。
    for (int lo = 0; lo <= 12; ++lo) {
        for (int hi = lo; hi <= 12; ++hi) {
            for (int answer = lo; answer <= hi; ++answer) {
                assert(firstTrue(lo, hi, [&](int x) { return x >= answer; }) == answer);
                assert(lastTrue(lo, hi, [&](int x) { return x <= answer; }) == answer);
            }
        }
    }
    assert(isLeap(2000) && !isLeap(1900) && isLeap(2024) && !isLeap(2023));
    assert(daysInMonth(2024, 2) == 29 && daysInMonth(2023, 2) == 28);
    assert(getDay(1970, 1, 1) == 4);
    assert(getDay(2024, 1, 1) == 1);
}

int main() {
    test();
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
