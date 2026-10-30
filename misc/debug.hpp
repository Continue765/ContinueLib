#pragma once
#include <bits/stdc++.h>
using namespace std;

#define dbg(...) do { cerr << "[" << __LINE__ << "] "; pr(__VA_ARGS__); cerr << '\n'; } while (0)

template <class T, class... U>
void pr(T x, U... y) {
    if constexpr (requires { cerr << x; }) {
        cerr << x;
    } else if constexpr (requires { tuple_size<T>::value; }) {
        cerr << '(';
        bool f = 0;
        apply([&](auto... e) { ((cerr << (exchange(f, 1) ? "," : ""), pr(e)), ...); }, x);
        cerr << ')';
    } else {
        cerr << '[';
        bool f = 0;
        for (auto e : x) cerr << (exchange(f, 1) ? "," : ""), pr(e);
        cerr << ']';
    }
    if constexpr (sizeof...(y)) cerr << "  ", pr(y...);
}
