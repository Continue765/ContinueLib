void dijkstra(int s, vector<vector<pair<int, i64>>>& adj, vector<i64>& dist, vector<int>& pre) {
    int n = adj.size();
    dist.assign(n, INF);
    pre.assign(n, -1);
    priority_queue<pair<i64, int>, vector<pair<i64, int>>, greater<pair<i64, int>>> pq;

    dist[s] = 0;
    pq.emplace(0, s);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) {
            continue;
        }
        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pre[v] = u;
                pq.emplace(dist[v], v);
            }
        }
    }
}