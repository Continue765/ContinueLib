void build(vector<vector<pair<int, i64>>>& vt, LCA& lca, vector<int> h, vector<int>& vis, int id) {
    auto& dfn = lca.dfn;
    auto& root = lca.root;
    sort(h.begin(), h.end(), [&](int x, int y) { return dfn[x] < dfn[y]; });
    h.erase(unique(h.begin(), h.end()), h.end());

    vector<int> stk;
    stk.push_back(root);

    auto addEdge = [&](int u, int v) -> void {
        if (vis[u] != id) {
            vt[u].clear();
            vis[u] = id;
        }
        if (vis[v] != id) {
            vt[v].clear();
            vis[v] = id;
        }
        i64 w = lca.getW(u, v);
        vt[u].emplace_back(v, w);
        vt[v].emplace_back(u, w);
    };

    for (auto& x : h) {
        if (x == root) {
            continue;
        }
        int l = lca.get(x, stk.back());
        if (l != stk.back()) {
            while (stk.size() >= 2 && dfn[l] < dfn[stk[stk.size() - 2]]) {
                int v = stk.back();
                stk.pop_back();
                int u = stk.back();
                addEdge(u, v);
            }
            if (dfn[l] > dfn[stk[stk.size() - 2]]) {
                int u = stk.back();
                addEdge(u, l);
                stk.back() = l;
            } else {
                int u = stk.back();
                stk.pop_back();
                addEdge(u, l);
            }
        }
        stk.push_back(x);
    }

    for (int i = 0; i < int(stk.size()) - 1; i++) {
        int u = stk[i], v = stk[i + 1];
        addEdge(u, v);
    }
}