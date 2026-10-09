#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "data_structure/cartesian_tree.hpp"

template <bool IsMin>
void checkCartesian(vector<int> a) {
    CartesianTree<int, IsMin> tree(a);
    auto before = [&](int x, int y) {
        if (a[x] != a[y]) return IsMin ? a[x] < a[y] : a[x] > a[y];
        return x < y;
    };
    int root = 0;
    for (int i = 1; i < (int)a.size(); ++i) if (before(i, root)) root = i;
    assert(tree.root == root);
    vector<int> seen(a.size());
    auto dfs = [&](auto&& self, int u) -> pair<int, int> {
        assert(u != -1 && !seen[u]);
        seen[u] = 1;
        int lo = u, hi = u + 1;
        for (int v : {tree.L[u], tree.R[u]}) {
            if (v == -1) continue;
            assert(tree.p[v] == u);
            assert(before(u, v));
            auto [l, r] = self(self, v);
            lo = min(lo, l);
            hi = max(hi, r);
        }
        assert(((tree.range[u] == pair<int, int>(lo, hi))));
        return {lo, hi};
    };
    dfs(dfs, tree.root);
    assert(all_of(seen.begin(), seen.end(), [](int x) { return x == 1; }));
}

int main() {
    checkCartesian<true>({4, 2, 2, 7, -1, 5, -1, 3});
    checkCartesian<false>({4, 2, 2, 7, -1, 5, -1, 3});
    checkCartesian<true>({9});

    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
