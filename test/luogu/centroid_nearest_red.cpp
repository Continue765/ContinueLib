#include <graph/tree/centroid.hpp>

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    Undigraph<int> g(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g.add(u - 1, v - 1);
    }
    Tree tree(g);
    vector<vector<pair<int, int>>> anc(n);
    centroidDecompsition(tree, [&](const vector<int>& fa,
                                 const vector<int>& vt,
                                 const vector<int>&) {
        int m = vt.size();
        vector<int> d(m);
        for (int i = 1; i < m; i++) {
            d[i] = d[fa[i]] + 1;
        }
        for (int i = 0; i < m; i++) {
            anc[vt[i]].emplace_back(vt[0], d[i]);
        }
    });

    vector<int> best(n, n);
    auto paint = [&](int u) {
        for (auto [c, d] : anc[u]) {
            best[c] = min(best[c], d);
        }
    };
    auto query = [&](int u) {
        int res = n;
        for (auto [c, d] : anc[u]) {
            res = min(res, d + best[c]);
        }
        return res;
    };

    paint(0);
    while (q--) {
        int op, u;
        cin >> op >> u;
        u--;
        if (op == 1) {
            paint(u);
        } else {
            cout << query(u) << '\n';
        }
    }
    return 0;
}
