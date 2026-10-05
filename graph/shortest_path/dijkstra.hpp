template <typename T>
pair<vector<T>, vector<int>> dijkstra(vector<vector<pair<int, T>>>& adj, int s) {
    int n = adj.size();
    vector<T> dist(n, inf);
    vector<int> pre(n, -1);
    using P =  pair<T, int>;
    priority_queue<P, vector<P>, greater<P>> pq;

    dist[s] = 0;
    pq.emplace(0, s);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) {
            continue;
        }
        for (auto& [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pre[v] = u;
                pq.emplace(dist[v], v);
            }
        }
    }

    return {dist, pre};
}

template <typename T>
pair<vector<T>, vector<int>> dijkstraDense(vector<vector<pair<int, T>>>& adj, int s) {
    int n = adj.size();
    vector<T> dist(n, inf);
    vector<int> pre(n, -1);
    vector<int> done(n, false);

    dist[s] = 0;

    for (int _ = 0; _ < n; _++) {
        int u = -1;
        for (int v = 0; v < n; v++) {
            if (!done[v] && (u == -1 || dist[v] < dist[u])) {
                u = v;
            }
        }
        if (u == -1 || dist[u] == inf) {
            break;
        }
        done[u] = true;
        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pre[v] = u;
            }
        }
    }

    return {dist, pre};
}

template <typename T>
tuple<vector<T>, vector<int>, vector<int>> dijkstra(vector<vector<pair<int, T>>>& adj, vector<int>& s) {
    int n = adj.size();
    vector<T> dist(n, inf);
    vector<int> pre(n, -1), root(n, -1);
    using P =  pair<T, int>;
    priority_queue<P, vector<P>, greater<P>> pq;

    for (auto& u : s) {
        dist[u] = 0;
        root[u] = u;
        pq.emplace(0, u);
    }

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) {
            continue;
        }
        for (auto& [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pre[v] = u;
                root[v] = root[u];
                pq.emplace(dist[v], v);
            }
        }
    }

    return {dist, pre, root};
}
