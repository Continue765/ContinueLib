#pragma once
#include <common.hpp>

template <typename T, bool IS_MIN = false>
struct CartesionTree {
    int n;
    vector<T>& a;
    vector<int> L, R;
    int root;

    CartesionTree(vector<T>& a_) : n(a_.size()), a(a_) {
        L.assign(n, -1);
        R.assign(n, -1);
        vector<int> stk;

        auto cmp = [&](int i, int j) -> bool {
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
            if (!stk.empty()) {
                R[stk.back()] = i;
            }

            stk.push_back(i);
        }
        int root = -1;
        while (!stk.empty()) {
            root = stk.back();
            stk.pop_back();
        }
    }
};