#pragma once
#include <common.hpp>

template <typename Fp>
vector<Fp> allInverse(const vector<Fp>& a) {
    for (auto& v : a) {
        assert(v != 0);
    }
    int n = a.size();
    vector<Fp> res(n + 1);
    res[0] = Fp{1};
    for (int i = 0; i < n; i++) {
        res[i + 1] = res[i] * a[i];
    }
    Fp inv = res[n].inverse();
    res.pop_back();
    for (int i = n - 1; i >= 0; i--) {
        res[i] *= inv;
        inv *= a[i];
    }
    return res;
}
