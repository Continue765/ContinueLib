#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B"
#include <common.hpp>
#include "flow/min_cost_flow.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; i64 need;
    cin >> n >> m >> need;
    MinCostFlow<i64> flow(n);
    while (m--) { int u, v; i64 cap, cost; cin >> u >> v >> cap >> cost; flow.addEdge(u, v, cap, cost); }
    auto [sent, cost] = flow.flow(0, n - 1, need);
    cout << (sent < need ? -1 : cost) << '\n';
}
