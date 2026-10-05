#pragma once
#include <common.hpp>
#include <algebra/monoid.hpp>

// Template
// struct ActMono {
//     using Mono = Mono;
//     using Tag = Tag;
//     using X = Mono::Type;
//     using Y = Tag::Type;
//     static X act(const X& x, const Y& y, int len) {
//         return {};
//     }
// };

// 区间和 + 区间加
template <typename T>
struct SumAdd {
    using Mono = AddMono<T>;
    using Tag = AddMono<T>;
    using X =  Mono::Type;
    using Y = Tag::Type;
    static X act(const X& x, const Y& y, int len) {
        return {x.v + y.k * len};
    }
};

// 区间和 + 区间乘
template <typename T>
struct SumMul {
    using Mono = AddMono<T>;
    using Tag = MulMono<T>;
    using X = Mono::Type;
    using Y = Tag::Type;
    static X act(const X& x, const Y& y, int len) {
        return {x.v * y.k};
    }
};

template <typename T>
struct MinAdd {
    using Mono = MinMono<T>;
    using Tag = AddMono<T>;
    using X = Mono::Type;
    using Y = Tag::Type;
    static X act(const X& x, const Y& y, int len) {
        return {x + y};
    }
};

template <typename T>
struct MaxAdd {
    using Mono = MaxMono<T>;
    using Tag = AddMono<T>;
    using X = Mono::Type;
    using Y = Tag::Type;
    static X act(const X& x, const Y& y, int len) {
        return {x + y};
    }
};