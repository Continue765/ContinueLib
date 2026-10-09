#define PROBLEM "https://judge.yosupo.jp/problem/two_sat"
#include <common.hpp>
#include "graph/twosat.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string p, cnf;
    int n, m;
    cin >> p >> cnf >> n >> m;
    TwoSat sat(n);
    vector<array<int, 4>> clauses(m);
    for (auto& c : clauses) {
        int a, b, zero; cin >> a >> b >> zero;
        int u = abs(a) - 1, v = abs(b) - 1;
        bool f = a > 0, g = b > 0;
        c = {u, int(f), v, int(g)};
        sat.addClause(u, f, v, g);
    }
    auto [ok, ans] = sat.satisfiable();
    if (!ok) { cout << "s UNSATISFIABLE\n"; return 0; }
    for (auto [u, f, v, g] : clauses) if (!(ans[u] == f || ans[v] == g)) return 1;
    cout << "s SATISFIABLE\nv";
    for (int i = 0; i < n; ++i) cout << ' ' << (ans[i] ? i + 1 : -i - 1);
    cout << " 0\n";
}
