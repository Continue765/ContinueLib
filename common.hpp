#pragma once
#include <bits/stdc++.h>
using namespace std;

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;

using i128 = __int128_t;
using u128 = __uint128_t;

template <typename T>
constexpr T inf = numeric_limits<T>::max() / 2;
template <>
constexpr int inf<int> = 1e9;
template <>
constexpr i64 inf<i64> = 1e18;