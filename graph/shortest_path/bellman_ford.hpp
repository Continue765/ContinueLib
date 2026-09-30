bool bellmanFord(int s, int n, const vector<Edge>& edges, vector<int>& dist) {
    dist.assign(n, INF);
    dist[s] = 0;

    for (int i = 0; i < n - 1; i++) {
        bool upd = false;
        for (auto& [u, v, w] : edges) {
            if (dist[u] == INF) {
                continue;
            }
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                upd = true;
            }
        }
        if (!upd) {
            break;
        }
    }

    for (auto& [u, v, w] : edges) {
        if (dist[u] == INF) {
            continue;
        }
        if (dist[v] > dist[u] + w) {
            return false;  // 有负环，不存在最短路
        }
    }

    return true;
}