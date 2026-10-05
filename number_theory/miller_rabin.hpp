#pragma once
#include <common.hpp>
#include <algebra/power.hpp>

bool isPrime(i64 n) {
    if (n < 2) {
        return false;
    }
    constexpr array<int, 10> smallPrimes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    for (auto& p : smallPrimes) {
        if (n % p == 0) {
            return n == p;
        }
    }
    if (n < 31 * 31) {
        return true;
    }
    constexpr array<int, 7> bases = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    int s = __builtin_ctzll(n - 1);
    i64 d = (n - 1) >> s;
    for (auto& a : bases) {
        if (a % n == 0) {
            continue;
        }
        i64 cur = power(a, d, n);
        if (cur == 1) {
            continue;
        }
        bool witness = true;
        for (int r = 0; r < s; r++) {
            if (cur == n - 1) {
                witness = false;
                break;
            }
            cur = mul(cur, cur, n);
        }
        if (witness) {
            return false;
        }
    }
    return true;
}
