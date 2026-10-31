#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "flow/max_flow.hpp"
#include "flow/min_cost_flow.hpp"

int main() {
    MaxFlow<int> mf(4);
    mf.addEdge(0, 1, 3); mf.addEdge(0, 2, 2); mf.addEdge(1, 2, 1); mf.addEdge(1, 3, 2); mf.addEdge(2, 3, 3);
    assert(mf.flow(0, 3) == 5);
    auto cut = mf.minCut();
    assert(cut[0] && !cut[3]);
    auto fedges = mf.edges();
    int total = 0;
    for (auto e : fedges) { assert(e.flow >= 0 && e.flow <= e.cap); if (e.from == 0) total += e.flow; }
    assert(total == 5 && fedges.size() == 5);
    assert(mf.flow(0, 3) == 0);
    mf = MaxFlow<int>(2); mf.addEdge(0, 1, 7);
    assert(mf.flow(0, 1) == 7 && mf.edges().size() == 1);
    MaxFlow<int> none(3); none.addEdge(0, 1, 4);
    assert(none.flow(0, 2) == 0 && none.minCut()[0] && !none.minCut()[2]);
    MinCostFlow<int> mcf(4);
    mcf.addEdge(0, 1, 2, 1); mcf.addEdge(0, 2, 1, 0);
    mcf.addEdge(1, 2, 1, -2); mcf.addEdge(1, 3, 1, 3); mcf.addEdge(2, 3, 2, 1);
    mcf.set(vector<int>{0, 1, -1, 0});
    auto [flow, cost] = mcf.flow(0, 3, 2);
    assert(flow == 2 && cost == 1);
    auto medges = mcf.edges();
    int used = 0;
    for (auto e : medges) { assert(e.flow >= 0 && e.flow <= e.cap); used += e.flow; }
    assert(used == 5 && medges.size() == 5);
    auto [more, more_cost] = mcf.flow(0, 3, 2);
    assert(more == 1 && more_cost == 4);
    mcf = MinCostFlow<int>(2); mcf.addEdge(0, 1, 7, 4);
    auto [all, all_cost] = mcf.flow(0, 1, 3);
    assert(all == 3 && all_cost == 12);
    MinCostFlow<int> unreachable(4);
    unreachable.addEdge(0, 1, 2, 3);
    unreachable.addEdge(1, 2, 1, 2);
    unreachable.set(vector<int>(4, 0));
    auto [partial, partial_cost] = unreachable.flow(0, 3, 5);
    assert(partial == 0 && partial_cost == 0);
    auto [available, available_cost] = unreachable.flow(0, 2, 5);
    assert(available == 1 && available_cost == 5);
    mt19937 rng(787154);
    for (int it = 0; it < 500; it++) {
        int n = 2 + rng() % 4, m = rng() % 8;
        MaxFlow<int> mf(n);
        struct E { int u, v, cap, cost; };
        vector<E> edges;
        for (int j = 0; j < m; j++) {
            int u = rng() % n, v = rng() % n, cap = rng() % 3;
            mf.addEdge(u, v, cap);
            edges.push_back({u, v, cap, 0});
        }
        int best = inf<int>;
        for (int mask = 0; mask < (1 << n); mask++) if ((mask & 1) && !(mask >> (n - 1) & 1)) {
            int cut = 0;
            for (auto e : edges) if ((mask >> e.u & 1) && !(mask >> e.v & 1)) cut += e.cap;
            best = min(best, cut);
        }
        assert(mf.flow(0, n - 1) == best);
        auto side = mf.minCut();
        int cut = 0;
        for (auto e : edges) if (side[e.u] && !side[e.v]) cut += e.cap;
        assert(side[0] && !side[n - 1] && cut == best);
        vector<int> balance(n);
        auto used = mf.edges();
        assert(used.size() == edges.size());
        for (int i = 0; i < m; i++) {
            auto e = used[i];
            assert(e.from == edges[i].u && e.to == edges[i].v && e.cap == edges[i].cap);
            assert(0 <= e.flow && e.flow <= e.cap);
            balance[e.from] -= e.flow; balance[e.to] += e.flow;
        }
        assert(balance[0] == -best && balance[n - 1] == best);
        for (int u = 1; u + 1 < n; u++) assert(balance[u] == 0);
    }
    for (int it = 0; it < 500; it++) {
        int n = 2 + rng() % 4, m = rng() % 7, need = rng() % 6;
        MinCostFlow<int> mcf(n);
        struct E { int u, v, cap, cost; };
        vector<E> edges;
        vector<int> potential(n), balance(n);
        for (int j = 0; j < m; j++) {
            int u = rng() % (n - 1), v = u + 1 + rng() % (n - u - 1);
            int cap = rng() % 3, cost = int(rng() % 9) - 3;
            edges.push_back({u, v, cap, cost});
            mcf.addEdge(u, v, cap, cost);
        }
        for (int u = 0; u < n; u++) for (auto e : edges) if (e.u == u && e.cap) {
            potential[e.v] = min(potential[e.v], potential[u] + e.cost);
        }
        mcf.set(potential);
        vector<int> costs(need + 1, inf<int>);
        auto brute = [&](auto&& self, int i, int cost) -> void {
            if (i == m) {
                for (int u = 1; u + 1 < n; u++) if (balance[u]) return;
                int sent = balance[n - 1];
                if (balance[0] == -sent && 0 <= sent && sent <= need) costs[sent] = min(costs[sent], cost);
                return;
            }
            auto e = edges[i];
            for (int x = 0; x <= e.cap; x++) {
                balance[e.u] -= x; balance[e.v] += x;
                self(self, i + 1, cost + x * e.cost);
                balance[e.u] += x; balance[e.v] -= x;
            }
        };
        brute(brute, 0, 0);
        int sent = need;
        while (costs[sent] == inf<int>) sent--;
        auto [actual, cost] = mcf.flow(0, n - 1, need);
        assert(actual == sent && cost == costs[sent]);
        int edgeCost = 0;
        auto used = mcf.edges();
        assert(used.size() == edges.size());
        for (int i = 0; i < m; i++) {
            auto e = used[i];
            assert(e.from == edges[i].u && e.to == edges[i].v && e.cap == edges[i].cap && e.cost == edges[i].cost);
            assert(0 <= e.flow && e.flow <= e.cap);
            balance[e.from] -= e.flow; balance[e.to] += e.flow;
            edgeCost += e.flow * e.cost;
        }
        assert(edgeCost == cost && balance[0] == -sent && balance[n - 1] == sent);
        for (int u = 1; u + 1 < n; u++) assert(balance[u] == 0);
    }
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
