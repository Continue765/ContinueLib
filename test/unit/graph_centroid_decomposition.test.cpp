#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <graph/tree/centroid.hpp>
#include <graph/tree/hld.hpp>

void checkTree(Graph<i64, false>& g, int root, bool heavy) {
    Tree tree(g, root);
    if (heavy) {
        HLD hld(tree);
    }
    int n = g.n;
    auto seq = tree.seq;
    auto in = tree.in;
    vector<vector<i64>> dist(n, vector<i64>(n));
    vector<vector<int>> hops(n, vector<int>(n));
    for (int s = 0; s < n; s++) {
        auto dfs = [&](auto&& self, int u, int p) -> void {
            for (auto [v, id] : g.adj[u]) {
                if (v == p) {
                    continue;
                }
                dist[s][v] = dist[s][u] + g.edges[id].w;
                hops[s][v] = hops[s][u] + 1;
                self(self, v, u);
            }
        };
        dfs(dfs, s, -1);
    }

    vector<int> centers(n);
    vector<vector<int>> pairs(n, vector<int>(n));
    vector<i64> ans(31), expected(31);
    auto count = [&](vector<i64> d, i64 k) -> i64 {
        sort(d.begin(), d.end());
        i64 res = 0;
        int l = 0, r = int(d.size()) - 1;
        while (l < r) {
            if (d[l] + d[r] <= k) {
                res += r - l;
                l++;
            } else {
                r--;
            }
        }
        return res;
    };
    centroidDecompsition(tree, [&](const vector<int>& par,
                                   const vector<int>& vs,
                                   const vector<int>& indptr) {
        int m = vs.size(), c = vs[0];
        assert(++centers[c] == 1);
        assert(par[0] == -1);
        assert(indptr[0] == 0 && indptr[1] == 1 && indptr.back() == m);
        vector<int> col(m), seen(n);
        vector<i64> d(m);
        for (int i = 0; i < m; i++) {
            assert(!seen[vs[i]]++);
        }
        for (int i = 1; i < m; i++) {
            assert(0 <= par[i] && par[i] < i);
            int u = vs[i], v = vs[par[i]];
            assert(hops[u][v] == 1);
            int x = tree.fa[u] == v ? u : v;
            d[i] = d[par[i]] + g.edges[tree.pe[x]].w;
            assert(d[i] == dist[c][u]);
        }
        for (int b = 1; b + 1 < int(indptr.size()); b++) {
            int l = indptr[b], r = indptr[b + 1];
            assert(l < r && r - l <= m / 2);
            for (int i = l; i < r; i++) {
                col[i] = b;
                assert(par[i] == 0 || (l <= par[i] && par[i] < r));
                assert((i == l) == (par[i] == 0));
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = i + 1; j < m; j++) {
                if (col[i] != col[j]) {
                    pairs[vs[i]][vs[j]]++;
                    pairs[vs[j]][vs[i]]++;
                    assert(d[i] + d[j] == dist[vs[i]][vs[j]]);
                }
            }
        }
        for (int k = -10; k <= 20; k++) {
            ans[k + 10] += count(d, k);
            for (int b = 1; b + 1 < int(indptr.size()); b++) {
                vector<i64> part(d.begin() + indptr[b], d.begin() + indptr[b + 1]);
                ans[k + 10] -= count(part, k);
            }
        }
    });
    assert(seq == tree.seq && in == tree.in);
    for (int u = 0; u < n; u++) {
        assert(centers[u] == 1);
        for (int v = u + 1; v < n; v++) {
            assert(pairs[u][v] == 1);
            for (int k = -10; k <= 20; k++) {
                expected[k + 10] += dist[u][v] <= k;
            }
        }
    }
    assert(ans == expected);
}

int main() {
    mt19937 rng(4178);
    for (int n = 1; n <= 60; n++) {
        for (int type = 0; type < 3; type++) {
            Graph<i64, false> g(n);
            for (int v = 1; v < n; v++) {
                int u = type == 0 ? v - 1 : type == 1 ? 0 : int(rng() % v);
                g.add(u, v, int(rng() % 16) - 5);
            }
            checkTree(g, 0, false);
            checkTree(g, rng() % n, false);
            checkTree(g, rng() % n, true);
        }
    }
    int a, b;
    if (cin >> a >> b) {
        cout << a + b << '\n';
    }
}
