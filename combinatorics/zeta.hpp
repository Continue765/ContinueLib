#pragma once
#include <common.hpp>

// 子集和：f[mask] = sum_{sub ⊆ mask} f[sub]
// 方向：小的 mask → 大的 mask（"吸收"不带的位）
template <typename T>
void subsetZeta(vector<T>& f) {
    int n = f.size();
    for (int i = 1; i < n; i <<= 1) {
        for (int mask = 0; mask < n; mask++) {
            if (mask & i) {
                f[mask] += f[mask ^ i];
            }
        }
    }
}

// 子集和的逆
template <typename T>
void subsetMobius(vector<T>& f) {
    int n = f.size();
    for (int i = 1; i < n; i <<= 1) {
        for (int mask = 0; mask < n; mask++) {
            if (mask & i) {
                f[mask] -= f[mask ^ i];
            }
        }
    }
}

// 超集和：f[mask] = sum_{sup ⊇ mask} f[sup]
// 方向：大的 mask → 小的 mask（"分发"给不带这一位的 mask）
template <typename T>
void supersetZeta(vector<T>& f) {
    int n = f.size();
    for (int i = 1; i < n; i <<= 1) {
        for (int mask = 0; mask < n; mask++) {
            if (mask & i) {
                f[mask ^ i] += f[mask];
            }
        }
    }
}

// 超集和的逆
template <typename T>
void supersetMobius(vector<T>& f) {
    int n = f.size();
    for (int i = 1; i < n; i <<= 1) {
        for (int mask = 0; mask < n; mask++) {
            if (mask & i) {
                f[mask ^ i] -= f[mask];
            }
        }
    }
}
