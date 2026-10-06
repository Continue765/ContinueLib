#pragma once
#include <common.hpp>

template <typename T, bool IS_MIN = false>
struct CartesianTree {
    int n;
    vector<T>& a;
    vector<int> L, R, p;
    // range[i]: the interval of the subtree rooted at i
    vector<pair<int, int>> range;
    int root;

    CartesianTree(vector<T>& a_) : n(a_.size()), a(a_), root(-1) {
        L.assign(n, -1);
        R.assign(n, -1);
        p.assign(n, -1);
        range.assign(n, {0, n});
        vector<int> stk;

        auto cmp = [&](int i, int j) -> bool {
            if (a[i] == a[j]) {
                return i < j;
            }
            if constexpr (IS_MIN) {
                return a[i] < a[j];
            } else {
                return a[j] < a[i];
            }
        };

        for (int i = 0; i < n; i++) {
            while (!stk.empty() && cmp(i, stk.back())) {
                L[i] = stk.back();
                stk.pop_back();
            }
            range[i].first = stk.empty() ? 0 : stk.back() + 1;
            if (!stk.empty()) {
                R[stk.back()] = i;
            }
            stk.push_back(i);
        }
        if (!stk.empty()) {
            root = stk.front();
        }
        stk.clear();
        for (int i = n - 1; i >= 0; i--) {
            while (!stk.empty() && cmp(i, stk.back())) {
                stk.pop_back();
            }
            range[i].second = stk.empty() ? n : stk.back();
            stk.push_back(i);
        }
        for (int i = 0; i < n; i++) {
            if (L[i] != -1) {
                p[L[i]] = i;
            }
            if (R[i] != -1) {
                p[R[i]] = i;
            }
        }
    }
};