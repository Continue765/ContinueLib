#pragma once
#include <common.hpp>

i64 exgcd(i64 a, i64 b, i64& x, i64& y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    i64 d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

i64 inv(i64 a, i64 m) {
    i64 x, y;
    i64 d = exgcd(a, m, x, y);
    if (d != 1) {
        return -1;
    }
    return (x % m + m) % m;
}

bool solveLinear(i64 a, i64 b, i64 c, i64& x, i64& y) {
    i64 d = exgcd(a, b, x, y);
    if (c % d != 0) {
        return false;
    }
    i64 k = c / d;
    x *= k;
    y *= k;
    return true;
}

pair<i64, i64> solveMod(i64 a, i64 b, i64 m) {
    assert(m > 0);
    b *= -1;
    i64 x, y;
    i64 g = exgcd(a, m, x, y);
    if (g < 0) {
        g *= -1;
        x *= -1;
        y *= -1;
    }
    if (b % g != 0) {
        return {-1, -1};
    }
    x = x * (b / g) % (m / g);
    if (x < 0) {
        x += m / g;
    }
    return {x, m / g};
}
