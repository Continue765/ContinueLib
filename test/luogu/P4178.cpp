#ifndef PROBLEM
#define PROBLEM "https://www.luogu.com.cn/problem/P4178"
#endif
#include <graph/tree/centroid.hpp>

i64 countPairs(vector<i64> d, i64 k) {
    sort(d.begin(), d.end());
    int l = 0, r = int(d.size()) - 1;
    i64 res = 0;
    while (l < r) {
        if (d[l] + d[r] <= k) {
            res += r - l;
            l++;
        } else {
            r--;
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    Graph<i64, false> g(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        i64 w;
        cin >> u >> v >> w;
        u--, v--;
        g.add(u, v, w);
    }

    i64 k;
    cin >> k;

    Tree tree(g);
    i64 ans = 0;

    centroidDecompsition(tree, [&](const vector<int>& fa, const vector<int>& vt, const vector<int>& pos) {
        int m = vt.size();
        vector<i64> d(m);
        for (int i = 1; i < m; i++) {
            int u = vt[i], v = vt[fa[i]];
            int x = (tree.fa[u] == v ? u : v);
            d[i] = d[fa[i]] + g.edges[tree.pe[x]].w;
        }
        ans += countPairs(d, k);
        for (int b = 1; b + 1 < int(pos.size()); b++) {
            vector<i64> part(d.begin() + pos[b], d.begin() + pos[b + 1]);
            ans -= countPairs(part, k);
        }
    });

    cout << ans << '\n';

    return 0;
}
