template <typename T>
pair<vector<T>, vector<int>> bfs_01(vector<vector<pair<int, T>>>& adj, int s) {
    int n = adj.size();
    vector<T> dist(n, inf);
    vector<int> pre(n, -1);
    deque<int> que;

    dist[s] = 0;
    que.push_front(s);

    while (!que.empty()) {
        auto u = que.front();
        que.pop_front();
        for (auto& [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pre[v] = u;
                if (w == 0) {
                    que.push_front(v);
                } else {
                    que.push_back(v);
                }
            }
        }
    }

    return {dist, pre};
}

template <typename T>
tuple<vector<T>, vector<int>, vector<int>> bfs_01(vector<vector<pair<int, T>>>& adj, vector<int>& s) {
    int n = adj.size();
    vector<T> dist(n, inf);
    vector<int> pre(n, -1), root(n, -1);
    deque<int> que;

    for (auto& u : s) {
        dist[u] = 0;
        root[u] = u;
        que.push_front(u);
    }

    while (!que.empty()) {
        auto u = que.front();
        que.pop_front();
        for (auto& [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pre[v] = u;
                root[v] = root[u];
                if (w == 0) {
                    que.push_front(v);
                } else {
                    que.push_back(v);
                }
            }
        }
    }

    return {dist, pre, root};
}
