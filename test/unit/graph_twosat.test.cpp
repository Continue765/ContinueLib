#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "graph/twosat.hpp"

int main() {
    TwoSat sat(3);
    sat.addClause(0, true, 1, true);
    sat.set(2, false);
    sat.implies(0, true, 2, false);
    auto [ok, ans] = sat.satisfiable();
    assert(ok && ans.size() == 3 && (ans[0] || ans[1]) && !ans[2]);
    TwoSat impossible(1);
    impossible.set(0, true);
    impossible.set(0, false);
    auto [bad, none] = impossible.satisfiable();
    assert(!bad && none.empty());
    for (bool f : {false, true}) for (bool g : {false, true}) {
        TwoSat forced(2);
        forced.set(0, f);
        forced.implies(0, f, 1, g);
        auto [ok, ans] = forced.satisfiable();
        assert(ok && ans[0] == f && ans[1] == g);
        forced.set(1, !g);
        assert(!forced.satisfiable().first);
        TwoSat vacuous(2);
        vacuous.set(0, !f);
        vacuous.set(1, !g);
        vacuous.implies(0, f, 1, g);
        assert(vacuous.satisfiable().first);
    }
    mt19937 rng(13661);
    for (int it = 0; it < 1000; it++) {
        int n = 1 + rng() % 7;
        TwoSat random(n);
        vector<array<int, 4>> clauses;
        for (int j = 0, m = rng() % 25; j < m; j++) {
            int u = rng() % n, v = rng() % n, f = rng() % 2, g = rng() % 2;
            if (rng() % 2) { random.addClause(u, f, v, g); clauses.push_back({u, f, v, g}); }
            else { random.implies(u, f, v, g); clauses.push_back({u, !f, v, g}); }
        }
        auto valid = [&](auto value) {
            for (auto [u, f, v, g] : clauses) if (value(u) != f && value(v) != g) return false;
            return true;
        };
        bool expected = false;
        for (int mask = 0; mask < (1 << n); mask++) expected |= valid([&](int u) { return mask >> u & 1; });
        auto [ok, ans] = random.satisfiable();
        assert(ok == expected);
        if (ok) assert(valid([&](int u) { return ans[u]; }));
    }
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
