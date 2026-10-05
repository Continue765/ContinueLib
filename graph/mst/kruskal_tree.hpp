struct KruskalTree {
    int n, root;
    vector<i64> val;
    vector<Edge> edges;
    vector<vector<int>> adj;

    KruskalTree(int n_) {
        init(n_);
    }

    void init(int n_) {
        n = n_;
        root = n - 1;
        val.assign(2 * n - 1, 0);
        adj.assign(2 * n - 1, vector<int>{});
        edges.clear();
    }

    void addEdge(int u, int v, i64 w) {
        edges.emplace_back(u, v, w);
    }

    void reconstruction() {
        DSU dsu(2 * n - 1);
        sort(edges.begin(), edges.end(), [](Edge& x, Edge& y) {
            return x.w < y.w;
        });

        for (auto& e : edges) {
            int u = e.u, v = e.v;
            i64 w = e.w;

            if (!dsu.same(u, v)) {
                u = dsu.find(u);
                v = dsu.find(v);
                val[++root] = w;

                adj[root].push_back(u);
                adj[root].push_back(v);
                adj[u].push_back(root);
                adj[v].push_back(root);

                dsu.f[u] = root;
                dsu.f[v] = root;
                dsu.siz[root] = dsu.siz[u] + dsu.siz[v];

                if (root == 2 * n - 2) {
                    return;
                }
            }
        }
    }
};