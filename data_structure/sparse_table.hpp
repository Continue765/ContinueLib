#pragma once
#include <common.hpp>

template <typename Mono>
struct SparseTable {
    using X = typename Mono::Type;

    int n;
    vector<vector<X>> st;

    SparseTable(const vector<X>& a) {
        init(a);
    }

    void init(const vector<X>& a) {
        n = a.size();
        int logn = __lg(n);
        st.assign(logn + 1, vector<X>(n));
        for (int i = 0; i < n; i++) {
            st[0][i] = a[i];
        }
        for (int j = 1; (1 << j) <= n; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[j][i] = Mono::op(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    X query(int l, int r) {
        assert(l < r);
        int len = r - l;
        int t = __lg(len);
        return Mono::op(st[t][l], st[t][r - (1 << t)]);
    }
};