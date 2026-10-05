template <typename T>
pair<vector<T>, vector<int>> spfa(vector<vector<pair<int, T>>>& adj, int s) {
    int n = adj.size();
    vector<T> dist(n, inf);
    vector<int> pre(n, -1);

    dist[s] = 0;

    queue<int> q;
    vector<char> inq(n, false);
    vector<int> cnt(n, 0);
    q.push(s);
    inq[s] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (auto& [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pre[v] = u;
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = true;
                    cnt[v]++;
                    if (cnt[v] >= n) {
                        return {{}, {}};
                    }
                }
            }
        }
    }

    return {dist, pre};
}
