#pragma once
#include <data_structure/dsu.hpp>
#include <graph/graph.hpp>

// 0: no Eulerian walk, 1: Eulerian path, 2: Eulerian circuit
template <typename T, bool directed>
int isEulerian(Graph<T, directed>& g, int s = -1) {
    int n = g.n;
    vector<int> deg(n);
    DSU dsu(n);
    for (auto& e : g.edges) {
        dsu.merge(e.u, e.v);
        deg[e.u]++;
        deg[e.v] += (directed ? -1 : 1);
    }
    int root = g.edges[0].u;
    for (auto& e : g.edges) {
        if (!dsu.same(root, e.u)) {
            return 0;
        }
    }
    if (s != -1 && !dsu.same(root, s)) {
        return 0;
    }
    int diff = 0;
    for (int u = 0; u < n; u++) {
        diff += directed ? abs(deg[u]) : (deg[u] & 1);
    }
    if (diff == 0) {
        return 2;
    }
    if (diff != 2) {
        return 0;
    }
    if (s == -1) {
        return 1;
    }
    return (directed ? deg[s] == 1 : (deg[s] & 1));
}

template <typename T, bool directed>
bool isEulerianPath(Graph<T, directed>& g, int s = -1) {
    return isEulerian(g, s) >= 1;
}
template <typename T, bool directed>
bool isEulerianCircuit(Graph<T, directed>& g, int s = -1) {
    return isEulerian(g, s) == 2;
}

template <typename T, bool directed>
pair<vector<int>, vector<int>> findEulerian(Graph<T, directed>& g, int s = -1) {
    int n = g.n;
    int m = g.edges.size();
    assert(n > 0);
    assert(s == -1 || (0 <= s && s < n));
    if (s == -1) {
        vector<int> deg(n);
        for (auto& e : g.edges) {
            deg[e.u]++;
            deg[e.v] += (directed ? -1 : 1);
        }
        if constexpr (directed) {
            s = max_element(deg.begin(), deg.end()) - deg.begin();
            if (deg[s] == 0) {
                s = m == 0 ? 0 : g.edges[0].u;
            }
        } else {
            s = (m == 0 ? 0 : g.edges[0].u);
            for (int u = 0; u < n; u++) {
                if (deg[u] & 1) {
                    s = u;
                    break;
                }
            }
        }
    }
    if (m == 0) {
        return {{s}, {}};
    }
    vector<int> bal(n), ptr(n), vs, es;
    vector<char> used(m, false);
    vector<pair<int, int>> stk = {{s, -1}};
    bal[s]++;
    while (!stk.empty()) {
        auto [u, eid] = stk.back();
        if (ptr[u] == int(g.adj[u].size())) {
            vs.push_back(u);
            if (eid != -1) {
                es.push_back(eid);
            }
            stk.pop_back();
        } else {
            auto [v, id] = g.adj[u][ptr[u]++];
            if (used[id]) {
                continue;
            }
            bal[u]--;
            bal[v]++;
            used[id] = true;
            stk.emplace_back(v, id);
        }
    }
    for (auto& x : bal) {
        if (x < 0) {
            return {{}, {}};
        }
    }
    if (int(vs.size()) != m + 1) {
        return {{}, {}};
    }
    reverse(vs.begin(), vs.end());
    reverse(es.begin(), es.end());
    return {vs, es};
}
