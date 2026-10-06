#pragma once
#include <common.hpp>

template <typename Mono>
typename Mono::Type power(typename Mono::Type a, i64 b) {
    if constexpr (requires { Mono::pow(a, b); }) {
        return Mono::pow(a, b);
    } else {
        auto res = Mono::e();
        while (b > 0) {
            if (b & 1) {
                res = Mono::op(res, a);
            }
            a = Mono::op(a, a);
            b >>= 1;
        }
        return res;
    }
}
