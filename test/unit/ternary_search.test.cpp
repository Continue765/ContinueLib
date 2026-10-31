#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "misc/ternary_search.hpp"

void test() {
    for (double center : {-20.0, -3.5, 0.0, 6.25, 20.0}) {
        double expected = clamp(center, -10.0, 10.0);
        auto quadratic = [&](double x) { return (x - center) * (x - center); };
        double minimum = ternarySearch(-10.0, 10.0, quadratic);
        assert(abs(minimum - expected) < 1e-5);
        double maximum = ternarySearch(-10.0, 10.0,
            [&](double x) { return -quadratic(x); }, greater<>{});
        assert(abs(maximum - expected) < 1e-5);
    }
    assert(ternarySearch(2.0, 2.0, [](double x) { return x * x; }) == 2.0);
    double flat = ternarySearch(-4.0, 7.0, [](double) { return 1.0; });
    assert(-4.0 <= flat && flat <= 7.0);
}

int main() {
    test();
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
