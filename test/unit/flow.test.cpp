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
    mf.init(2); mf.addEdge(0, 1, 7);
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
    mcf.init(2); mcf.addEdge(0, 1, 7, 4);
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
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
