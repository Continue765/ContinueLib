bool spfa(int s, int n, vector<vector<pair<int, i64>>>& adj, vector<i64>& dist) {
    dist.assign(n, inf);
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
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = true;
                    cnt[v]++;
                    if (cnt[v] >= n) {
                        return false;  // 有负环
                    }
                }
            }
        }
    }

    return true;
}
