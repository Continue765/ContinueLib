template<typename T>
struct MinCostFlow {
    struct Edge_ {
        int to;
        T cap;
        T cost;
        Edge_(int to_, T cap_, T cost_) : to(to_), cap(cap_), cost(cost_) {}
    };

    int n;
    vector<Edge_> e;
    vector<vector<int>> adj;
    vector<T> h, dist;
    vector<int> pre;

    bool dijkstra(int s, int t) {
        dist.assign(n, numeric_limits<T>::max());
        pre.assign(n, -1);
        priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> que;
        dist[s] = 0;
        que.emplace(0, s);
        while (!que.empty()) {
            auto [d, u] = que.top();
            que.pop();
            if (dist[u] != d) {
                continue;
            }
            for (auto& i : adj[u]) {
                int v = e[i].to;
                if (e[i].cap > 0 && dist[v] > d + h[u] - h[v] + e[i].cost) {
                    dist[v] = d + h[u] - h[v] + e[i].cost;
                    pre[v] = i;
                    que.emplace(dist[v], v);
                }
            }
        }
        return dist[t] != numeric_limits<T>::max();
    }

    MinCostFlow() {}
    MinCostFlow(int n_) {
        init(n_);
    }

    void init(int n_) {
        n = n_;
        e.clear();
        adj.assign(n, {});
    }

    void addEdge(int u, int v, T cap, T cost) {
        adj[u].push_back(e.size());
        e.emplace_back(v, cap, cost);
        adj[v].push_back(e.size());
        e.emplace_back(u, 0, -cost);
    }

    pair<T, T> flow(int s, int t, T need = numeric_limits<T>::max(), vector<T> potential = {}) {
        T flow = 0;
        T cost = 0;
        if (potential.empty()) {
            potential.assign(n, 0);
        }
        h = potential;
        while (flow < need && dijkstra(s, t)) {
            for (int i = 0; i < n; ++i) {
                h[i] += dist[i];
            }
            T aug = numeric_limits<T>::max();
            for (int i = t; i != s; i = e[pre[i] ^ 1].to) {
                aug = min(aug, e[pre[i]].cap);
            }
            for (int i = t; i != s; i = e[pre[i] ^ 1].to) {
                e[pre[i]].cap -= aug;
                e[pre[i] ^ 1].cap += aug;
            }
            flow += aug;
            cost += aug * h[t];
        }
        return {flow, cost};
    }

    struct Edge {
        int from;
        int to;
        T cap;
        T cost;
        T flow;
    };

    vector<Edge> edges() {
        vector<Edge> a;
        for (int i = 0; i < e.size(); i += 2) {
            Edge x;
            x.from = e[i + 1].to;
            x.to = e[i].to;
            x.cap = e[i].cap + e[i + 1].cap;
            x.cost = e[i].cost;
            x.flow = e[i + 1].cap;
            a.push_back(x);
        }
        return a;
    }
};