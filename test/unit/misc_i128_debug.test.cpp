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
