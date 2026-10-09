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
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
