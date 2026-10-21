#pragma once
#include <common.hpp>

template <typename Mono>
struct DisjointSparseTable {
    using X = typename Mono::Type;

    int n;
    vector<vector<X>> mat;

    DisjointSparseTable() : n(0) {}
    DisjointSparseTable(const vector<X>& a) : n(a.size()) {
        mat.push_back(a);
        for (int p = 1; (1 << p) < n; p++) {
            mat.emplace_back(n);
            for (int mid = 1 << p; mid < n; mid += (1 << (p + 1))) {
                mat[p][mid - 1] = a[mid - 1];
                for (int j = mid - 2; j >= mid - (1 << p); j--) {
                    mat[p][j] = Mono::op(a[j], mat[p][j + 1]);
                }
                mat[p][mid] = a[mid];
                for (int j = mid + 1; j < min(n, mid + (1 << p)); j++) {
                    mat[p][j] = Mono::op(mat[p][j - 1], a[j]);
                }
            }
        }
    }

    X query(int l, int r) {
        assert(0 <= l && l < r && r <= n);
        if (r - l == 1) {
            return mat[0][l];
        }
        int p = __lg(l ^ (r - 1));
        return Mono::op(mat[p][l], mat[p][r - 1]);
    }
};