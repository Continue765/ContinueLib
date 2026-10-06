#pragma once
#include <common.hpp>
#include <data_structure/dsu.hpp>
#include <graph/base.hpp>

// return:
// 0 - isn't Eulerian path
// 1 - is Eulerian path
// 2 - is Eulerian circuit
template <typename T>
int isEulerian(vector<vector<pair<int, T>>>& adj, bool directed = true, int s = -1) {
    int n = adj.size();
    // in and out are only for directed graph
    vector<int> in(n, 0), out(n, 0), deg(n, 0);
    DSU dsu(n);
    for (int u = 0; u < n; u++) {
        for (auto& [v, w] : adj[u]) {
            dsu.merge(u, v);
            if (directed) {
                out[u]++;
                in[v]++;
                deg[v]++;
            }
            deg[u]++;
        }
    }

    int root = -1;
    for (int u = 0; u < n; u++) {
        if (deg[u] == 0) {
            continue;
        }
        if (root == -1) {
            root = u;
        } else if (!dsu.same(root, u)) {
            return 0;
        }
    }

    if (s != -1 && root != -1 && !dsu.same(s, root)) {
        return 0;
    }

    if (directed) {
        int diff = 0;
        for (int u = 0; u < n; u++) {
            diff += abs(out[u] - in[u]);
        }
        if (diff == 0) {
            return 2;
        } else if (diff == 2) {
            if (s == -1) {
                return 1;
            } else {
                return (out[s] == in[s] + 1);
            }
        } else {
            return 0;
        }
    } else {
        int odd = 0;
        for (int u = 0; u < n; u++) {
            odd += (deg[u] & 1);
        }
        if (odd == 0) {
            return 2;
        } else if (odd == 2) {
            if (s == -1) {
                return 1;
            } else {
                return (deg[s] & 1);
            }
        } else {
            return 0;
        }
    }
}

template <typename T>
bool isEulerianPath(vector<vector<pair<int, T>>>& adj, bool directed = true, int s = -1) {
    return isEulerian(adj, directed, s) >= 1;
}
template <typename T>
bool isEulerianCircuit(vector<vector<pair<int, T>>>& adj, bool directed = true, int s = -1) {
    return isEulerian(adj, directed, s) == 2;
}

template <typename T>
pair<vector<int>, vector<Edge<T>>> findEulerian(vector<vector<pair<int, T>>>& adj, int s = -1) {
    // TODO
}
