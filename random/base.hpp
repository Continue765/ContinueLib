#pragma once
#include <common.hpp>

static mt19937_64 rng(static_cast<u64>(chrono::steady_clock::now().time_since_epoch().count()));

i64 randInt(i64 l, i64 r) {
    assert(l < r);
    return uniform_int_distribution<i64>(l, r - 1)(rng);
}

u64 randInt(u64 n) {
    assert(n > 0);
    return uniform_int_distribution<u64>(0, n - 1)(rng);
}

bool randBool() {
    return randInt(2);
}

double randReal(double lo, double hi) {
    assert(lo < hi);
    return uniform_real_distribution<double>(lo, hi)(rng);
}