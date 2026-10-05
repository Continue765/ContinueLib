#pragma once
#include <common.hpp>

int build(const vector<int>& a, vector<int>& L, vector<int>& R) {
    int n = a.size();
    L.assign(n, -1);
    R.assign(n, -1);

    stack<int> stk;
    for (int i = 0; i < n; i++) {
        while (!stk.empty() && a[stk.top()] < a[i]) {
            L[i] = stk.top();
            stk.pop();
        }

        if (!stk.empty()) {
            R[stk.top()] = i;
        }

        stk.push(i);
    }

    int root = -1;
    while (!stk.empty()) {
        root = stk.top();
        stk.pop();
    }
    return root;
}
