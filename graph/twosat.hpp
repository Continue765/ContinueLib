#pragma once
#include <common.hpp>
#include <graph/components/scc.hpp>

struct TwoSat {
    int n;
    SCC scc;
    vector<int> ans;

    TwoSat(int n_) : n(n_), scc(2 * n), ans(n) {}

    // add clause: (x_u = f) ∨ (x_v = g)
    void addClause(int u, bool f, int v, bool g) {
        scc.addEdge(2 * u + !f, 2 * v + g);
        scc.addEdge(2 * v + !g, 2 * u + f);
    }

    // (x_u = f)
    void set(int u, bool f) {
        addClause(u, f, u, f);
    }

    // (x_u = f) -> (x_v = g)
    void implies(int u, int f, int v, int g) {
        addClause(u, !f, v, g);
    }

    pair<bool, vector<int>> satisfiable() {
        auto id = scc.work();
        for (int i = 0; i < n; i++) {
            if (id[2 * i] == id[2 * i + 1]) {
                return {false, {}};
            }
            ans[i] = id[2 * i] < id[2 * i + 1];
        }
        return {true, ans};
    }
};
