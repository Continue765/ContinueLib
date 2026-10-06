#pragma once
#include <common.hpp>

i64 mul(i64 a, i64 b, i64 m) {
    return static_cast<i128>(a) * b % m;
}

i64 power(i64 a, i64 b, i64 m) {
    i64 res = 1 % m;
    while (b > 0) {
        if (b & 1) {
            res = mul(res, a, m);
        }
        a = mul(a, a, m);
        b >>= 1;
    }
    return res;
}

template <typename T, std::integral U>
constexpr T power(T a, U b) {
    assert(b >= 0);
    T res{1};
    while (b) {
        if (b & 1) {
            res *= a;
        }
        b >>= 1;
        a *= a;
    }
    return res;
}