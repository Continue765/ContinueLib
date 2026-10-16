#define PROBLEM "https://www.luogu.com.cn/problem/P4178"
#include <graph/centroid_decomposition.hpp>

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
        g.add(u - 1, v - 1, w);
    }
    i64 k;
    cin >> k;
    Tree tree(g);
    i64 ans = 0;
    centroidDecomposition(tree, [&](const vector<int>& par,
                                   const vector<int>& vs,
                                   const vector<int>& indptr) {
        int m = vs.size();
        vector<i64> d(m);
        for (int i = 1; i < m; i++) {
            int u = vs[i], v = vs[par[i]];
            int x = tree.fa[u] == v ? u : v;
            d[i] = d[par[i]] + g.edges[tree.pe[x]].w;
        }
        ans += countPairs(d, k);
        for (int b = 1; b + 1 < int(indptr.size()); b++) {
            vector<i64> part(d.begin() + indptr[b], d.begin() + indptr[b + 1]);
            ans -= countPairs(part, k);
        }
    });
    cout << ans << '\n';
}
