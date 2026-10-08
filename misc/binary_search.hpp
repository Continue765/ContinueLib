#pragma once
#include <common.hpp>

template <typename T, typename F>
T firstTrue(T lo, T hi, F&& pred) {
    while (lo < hi) {
        T mid = (lo + hi) / 2;
        if (pred(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return lo;
}

template <typename T, typename F>
T lastTrue(T lo, T hi, F&& pred) {
    while (hi - lo > 1) {
        T mid = (lo + hi) / 2;
        if (pred(mid)) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    return lo;
}