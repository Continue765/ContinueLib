#include "../edge.hpp"
#include "../../data_structure/dsu.hpp"

template <typename T>
pair<vector<Edge<T>>, T> boruvka(vector<Edge<T>>& edges, int n) {
    T cost = 0;
    vector<Edge<T>> res;
    DSU dsu(n);
    int cnt = n;

    while (cnt > 1) {
        vector<int> best(n, -1);
        int m = edges.size();

        for (int i = 0; i < m; i++) {
            auto& e = edges[i];
            int u = dsu.find(e.u);
            int v = dsu.find(e.v);
            if (u == v) {
                continue;
            }
            if (best[u] == -1 || e.w < edges[best[u]].w) {
                best[u] = i;
            }
            if (best[v] == -1 || e.w < edges[best[v]].w) {
                best[v] = i;
            }
        }

        bool upd = false;
        for (int u = 0; u < n; u++) {
            if (best[u] == -1) {
                continue;
            }
            auto& e = edges[best[u]];
            if (dsu.merge(e.u, e.v)) {
                res.push_back(e);
                cost += e.w;
                cnt--;
                upd = true;
            }
        }
        if (!upd) {
            break;
        }
    }

    return {res, cost};
}
