template <typename T>
struct Edge {
    int u, v;
    T w;
    Edge() {}
    Edge(int u_, int v_, T w_) : u(u_), v(v_), w(w_) {}
};

template <typename T>
struct Graph {
    vector<Edge<T>> edges;
    vector<vector<pair<int, T>>> adj;
    int n;

    Graph() : n(0) {}
    Graph(int n_) : n(n_) {
        adj.resize(n);
    }

    void addEdge(int u, int v, T w = {0}) {
        edges.emplace_back(u, v, w);
        adj[u].emplace_back(v, w);
    }
};