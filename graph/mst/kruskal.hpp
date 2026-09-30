vector<Edge> kruskal(vector<Edge>& edges, int n) {
    ranges::sort(edges, [](Edge& x, Edge& y) {
        return x.w < y.w;
    });

    DSU dsu(n);
    vector<Edge> res;

    for (auto& e : edges) {
        if (dsu.merge(e.u, e.v)) {
            res.push_back(e);
            if (res.size() == n - 1) {
                break;
            }
        }
    }

    return res;
}