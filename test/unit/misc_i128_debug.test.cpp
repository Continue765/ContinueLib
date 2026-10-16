#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "misc/debug.hpp"
#include "misc/i128.hpp"

void test() {
    i128 n = toi128("123456789012345678901234567890");
    assert(n == i128(12345678901234567890ULL) * 10000000000 + 1234567890);
    ostringstream out;
    out << n;
    assert(out.str() == "123456789012345678901234567890");
    assert(sqrti128(0) == 0 && sqrti128(80) == 8 && sqrti128(81) == 9);
    assert(sqrti128(i128(1000000000000LL) * 1000000000000LL) == 1000000000000LL);
    assert(gcd(i128(84), i128(30)) == 6);
    i128 max = i128((u128(1) << 127) - 1), min = -max - 1;
    assert(toi128("-123") == -123);
    assert(toi128("170141183460469231731687303715884105727") == max);
    assert(toi128("-170141183460469231731687303715884105728") == min);
    ostringstream negative;
    negative << i128(-123) << ' ' << min;
    assert(negative.str() == "-123 -170141183460469231731687303715884105728");
    for (i128 x : {i128(0), i128(123), i128(-123), max, min}) {
        ostringstream text;
        text << x;
        assert(!text.str().empty() && toi128(text.str()) == x);
    }
    assert(toi128("+123") == 123);
    for (i128 x : {i128(1), i128(10000000000000000LL), i128(1000000000000000000LL)}) {
        assert(sqrti128(x * x) == x);
        assert(sqrti128(x * x - 1) == x - 1);
        assert(sqrti128(x * x + 1) == (x == 1 ? 1 : x));
    }
    i128 r = sqrti128(max);
    assert(r <= max / r && r + 1 > max / (r + 1));
    ostringstream log;
    auto* old = cerr.rdbuf(log.rdbuf());
    dbg(vector<int>{1, 2, 3});
    cerr.rdbuf(old);
    assert(log.str().find("[1,2,3]") != string::npos);
}

int main() {
    test();
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
