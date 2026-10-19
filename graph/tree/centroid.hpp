#pragma once
#include <graph/tree/tree.hpp>

// f(fa, vt, pos)，局部编号 0 为重心，各分支占连续区间。
template <typename T, typename F>
void centroidDecompsition(const Tree<T>& tree, F&& f) {
    const auto& g = tree.g;
    vector<int> dead(tree.n), siz, fa, vt, pos;
    auto collect = [&](int u, int p) {
        int l = vt.size();
        vt.push_back(u);
        fa.push_back(p);
        for (int i = l; i < int(vt.size()); i++) {
            int u = vt[i];
            for (auto [v, id] : g[u]) {
                if (dead[v] || (fa[i] != -1 && v == vt[fa[i]])) {
                    continue;
                }
                vt.push_back(v);
                fa.push_back(i);
            }
        }
    };
    vector<int> roots{tree.root};
    for (int t = 0; t < int(roots.size()); t++) {
        vt.clear();
        fa.clear();
        collect(roots[t], -1);
        int m = vt.size(), c = -1;
        siz.assign(m, 1);
        for (int i = m - 1; i >= 0; i--) {
            if (siz[i] >= (m + 1) / 2) {
                c = vt[i];
                break;
            }
            siz[fa[i]] += siz[i];
        }
        dead[c] = true;
        vt = {c};
        fa = {-1};
        pos = {0, 1};
        for (auto [v, id] : g[c]) {
            if (!dead[v]) {
                roots.push_back(v);
                collect(v, 0);
                pos.push_back(vt.size());
            }
        }
        f(fa, vt, pos);
    }
}
