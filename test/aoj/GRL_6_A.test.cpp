#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A"
#include <common.hpp>
#include "flow/max_flow.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    MaxFlow<i64> flow(n);
    while (m--) { int u, v; i64 c; cin >> u >> v >> c; flow.addEdge(u, v, c); }
    cout << flow.flow(0, n - 1) << '\n';
}
