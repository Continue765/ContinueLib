#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "algebra/act.hpp"
#include "algebra/power.hpp"

struct StringConcat {
    using Type = string;
    static Type e() { return {}; }
    static Type op(const Type& a, const Type& b) { return a + b; }
};

void test() {
    assert(AddMono<i64>::e() == 0);
    assert(AddMono<i64>::op(4, -9) == -5);
    assert(AddMono<i64>::inv(7) == -7);
    assert(AddMono<i64>::pow(3, 4) == 12);
    assert(MulMono<i64>::e() == 1);
    assert(MulMono<i64>::op(6, 7) == 42);
    assert(MinMono<int>::op(8, -2) == -2);
    assert(MinMono<int>::pow(8, 0) == inf<int>);
    assert(MaxMono<int>::op(8, -2) == 8);
    assert(MaxMono<int>::pow(-3, 0) == -inf<int>);
    assert(GcdMono<i64>::op(18, 24) == 6);
    assert(LcmMono<i64>::op(6, 10) == 30);
    assert(XorMono<int>::op(5, 3) == 6);
    assert(XorMono<int>::power(7, 2) == 0);
    assert(power<AddMono<i64>>(5, 6) == 30);
    assert(power<MulMono<i64>>(3, 4) == 81);
    assert(power<MinMono<int>>(9, 0) == inf<int>);
    assert(power<StringConcat>(string("ab"), 3) == "ababab");
    assert(SumAdd<i64>::act(10, 4, 3) == 22);
    assert(SumMul<i64>::act(10, 4, 3) == 40);
    assert(MinAdd<i64>::act(-5, 4, 2) == -1);
    assert(MaxAdd<i64>::act(7, -3, 5) == 4);
}

int main() {
    test();
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
