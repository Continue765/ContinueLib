#pragma once
#include <common.hpp>

template <typename T, typename F, typename C = less<>>
T ternarySearch(T lo, T hi, F&& f, C&& comp = {}) {
    for (int i = 0; i < 100; i++) {
        T m1 = lo + (hi - lo) / 3;
        T m2 = hi - (hi - lo) / 3;
        if (comp(f(m1), f(m2))) {
            hi = m2;
        } else {
            lo = m1;
        }
    }
    return (lo + hi) / 2;
}
