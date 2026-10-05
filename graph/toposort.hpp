template <typename T>
vector<int> toposort(vector<vector<pair<int, T>>>& adj) {
    int n = adj.size();
    vector<int> topo, deg(n, 0);
    for (int u = 0; u < n; u++) {
        for (auto& [v, w] : adj[u]) {
            deg[v]++;
        }
    }
    for (int u = 0; u < n; u++) {
        if (deg[u] == 0) {
            topo.push_back(u);
        }
    }
    for (int i = 0; i < int(topo.size()); i++) {
        int u = topo[i];
        for (auto& [v, w] : adj[u]) {
            if (--deg[v] == 0) {
                topo.push_back(v);
            }
        }
    }
    return (int(topo.size()) != n ? vector<int>() : topo);
}

template <typename T>
vector<int> lexMinToposort(vector<vector<pair<int, T>>>& adj) {
    int n = adj.size();
    vector<int> topo, deg(n, 0);
    for (int u = 0; u < n; u++) {
        for (auto& [v, w] : adj[u]) {
            deg[v]++;
        }
    }
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int u = 0; u < n; u++) {
        if (deg[u] == 0) {
            pq.push(u);
        }
    }
    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();
        topo.push_back(u);
        for (auto& [v, w] : adj[u]) {
            if (--deg[v] == 0) {
                pq.push(v);
            }
        }
    }
    return (int(topo.size()) != n ? vector<int>() : topo);
}