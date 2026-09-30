struct BlockCutTree {
    int n;
    vector<pair<int, int>> edges;
    vector<vector<pair<int, int>>> adj;
    vector<int> stk;
    vector<int> dfn, low, cut;
    vector<vector<int>> comp;
    vector<vector<int>> tree;
    int cur;
    int tot;

    BlockCutTree() {}
    BlockCutTree(int n_) {
        init(n_);
    }

    void init(int n_) {
        n = n_;
        adj.assign(n, {});
        edges.clear();
        dfn.assign(n, -1);
        low.resize(n);
        stk.clear();
        comp.clear();
        cut.assign(n, false);
        tree.assign(n, {});
        tot = n;
        cur = 0;
    }

    void addEdge(int u, int v) {
        adj[u].emplace_back(v, edges.size());
        adj[v].emplace_back(u, edges.size());
        edges.emplace_back(u, v);
    }

    void addBlock(vector<int>& b) {
        int x = tot++;
        tree.emplace_back();
        vector<int> pts;
        for (auto& e : b) {
            auto [u, v] = edges[e];
            pts.push_back(u);
            pts.push_back(v);
        }
        sort(pts.begin(), pts.end());
        pts.erase(unique(pts.begin(), pts.end()), pts.end());
        for (int u : pts) {
            tree[u].push_back(x);
            tree[x].push_back(u);
        }
    }

    void dfs(int u, int p) {
        dfn[u] = low[u] = cur++;
        int child = 0;
        for (auto& [v, eid] : adj[u]) {
            if (eid == p) {
                continue;
            }
            if (dfn[v] == -1) {
                child++;
                stk.push_back(eid);
                dfs(v, eid);
                low[u] = min(low[u], low[v]);
                if (low[v] >= dfn[u]) {
                    if (p != -1) {
                        cut[u] = true;
                    }
                    vector<int> b;
                    while (true) {
                        int e = stk.back();
                        stk.pop_back();
                        b.push_back(e);
                        if (e == eid) {
                            break;
                        }
                    }
                    comp.push_back(b);
                    addBlock(b);
                }
            } else if (dfn[v] < dfn[u]) {
                stk.push_back(eid);
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (p == -1 && child >= 2) {
            cut[u] = true;
        }
    }

    void build() {
        for (int i = 0; i < n; i++) {
            if (dfn[i] == -1) {
                dfs(i, -1);
            }
        }
    }
};