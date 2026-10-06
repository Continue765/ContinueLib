#pragma once
#include <common.hpp>

// Template
// struct Monoid {
//     struct Type {
//         i64 v;
//     };
//     static Type e() {
//         return {};
//     }
//     static Type op(const Type& a, const Type& b) {
//         return {};
//     }
//     static Type from(const i64& x) {
//         return {x};
//     }
// };

template <typename T>
struct AddMono {
    using Type = T;
    static Type e() {
        return {0};
    }
    static Type op(const Type& a, const Type& b) {
        return {a + b};
    }
    static Type from(const i64& x) {
        return {x};
    }
    static Type inv(const Type& a) {
        return {-a};
    }
    static Type power(const Type& a, i64 k) {
        return a * k;
    }
};

template <typename T>
struct MulMono {
    using Type = T;
    static Type e() {
        return {1};
    }
    static Type op(const Type& a, const Type& b) {
        return {a * b};
    }
    static Type from(const i64& x) {
        return {x};
    }
};

template <typename T>
struct MinMono {
    using Type = T;
    static Type e() {
        return {inf<T>};
    }
    static Type op(const Type& a, const Type& b) {
        return {min(a, b)};
    }
    static Type from(const i64& x) {
        return {x};
    }
};

template <typename T>
struct MaxMono {
    using Type = T;
    static Type e() {
        return {-inf<T>};
    }
    static Type op(const Type& a, const Type& b) {
        return {max(a, b)};
    }
    static Type from(const i64& x) {
        return {x};
    }
};

template <typename T>
struct GcdMono {
    using Type = T;
    static Type e() {
        return {0};
    }
    static Type op(const Type& a, const Type& b) {
        return {gcd(a, b)};
    }
    static Type from(const i64& x) {
        return {x};
    }
};

template <typename T>
struct LcmMono {
    using Type = T;
    static Type e() {
        return {1};
    }
    static Type op(const Type& a, const Type& b) {
        return {lcm(a, b)};
    }
    static Type from(const i64& x) {
        return {x};
    }
};