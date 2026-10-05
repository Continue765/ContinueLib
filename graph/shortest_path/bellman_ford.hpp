template <typename T>
pair<vector<T>, vector<int>> bellmanFord(vector<vector<pair<int, T>>>& adj, int s) {
    int n = adj.size();
    vector<T> dist(n, inf);
    vector<int> pre(n, -1);

    dist[s] = 0;

    for (int round = 1;; round++) {
        bool upd = false;
        for (int u = 0; u < n; u++) {
            if (dist[u] == inf) {
                continue;
            }
            for (auto& [v, w] : adj[u]) {
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pre[v] = u;
                    upd = true;
                    if (round >= n) {
                        return {{}, {}};
                    }
                }
            }
        }
        if (!upd) {
            break;
        }
    }

    return {dist, pre};
}