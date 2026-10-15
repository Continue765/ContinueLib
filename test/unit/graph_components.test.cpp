#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "graph/components/scc.hpp"
#include "graph/components/ebcc.hpp"
#include "graph/components/vbcc.hpp"
#include "graph/components/block_cut_tree.hpp"

int main() {
    Graph<> directed(5);
    directed.add(0, 1); directed.add(1, 0); directed.add(1, 2);
    directed.add(2, 3); directed.add(3, 2);
    auto [cnt, id] = SCC(directed);
    assert(cnt == 3 && id[0] == id[1] && id[2] == id[3]);
    assert(id[0] < id[2] && id[4] != id[0] && id[4] != id[2]);
    assert(SCC(directed) == make_pair(cnt, id));
    Graph<> dag(2);
    dag.add(0, 1);
    auto [dc, di] = SCC(dag);
    assert(dc == 2 && di[0] < di[1]);

    Graph<int, false> g(5);
    g.add(0, 1); g.add(1, 2); g.add(2, 0); g.add(2, 3);
    auto [ec, eb] = EBCC(g);
    assert(ec == 3 && eb[0] == eb[1] && eb[1] == eb[2]);
    assert(eb[2] != eb[3] && eb[4] != eb[3] && eb[4] != eb[0]);
    auto [comp, cut] = VBCC(g);
    for (auto& block : comp) sort(block.begin(), block.end());
    sort(comp.begin(), comp.end());
    assert((comp == vector<vector<int>>{{0, 1, 2}, {3}}));
    assert((cut == vector<int>{0, 0, 1, 0, 0}));
    BlockCutTree bct(g);
    assert(bct.isCut(2) && !bct.isCut(0));
    assert(bct.tot == 7 && bct.tree.n == 7 && bct.tree.adj[2].size() == 2);
    assert(bct.tree.adj[4].empty());
    vector<vector<int>> blocks;
    for (int u = g.n; u < bct.tot; ++u) {
        vector<int> block;
        for (auto [v, eid] : bct.tree.adj[u]) block.push_back(v);
        sort(block.begin(), block.end());
        blocks.push_back(block);
    }
    sort(blocks.begin(), blocks.end());
    assert((blocks == vector<vector<int>>{{0, 1, 2}, {2, 3}}));

    // 重边共享端点，但有独立编号；它们之间不存在桥。
    Graph<int, false> parallel(3);
    parallel.add(0, 1, 8); parallel.add(0, 1, 3); parallel.add(1, 2, 5);
    auto [pc, pi] = EBCC(parallel);
    assert(pc == 2 && pi[0] == pi[1] && pi[1] != pi[2]);
    auto [pb, cuts] = VBCC(parallel);
    for (auto& block : pb) sort(block.begin(), block.end());
    sort(pb.begin(), pb.end());
    assert((pb == vector<vector<int>>{{0, 1}, {2}}));
    assert((cuts == vector<int>{0, 1, 0}));
    bct.init(parallel);
    assert(bct.n == 3 && bct.tot == 5 && bct.isCut(1));
    Graph<int, false> single(1);
    auto [sc, si] = EBCC(single);
    assert(sc == 1 && si == vector<int>{0});
    auto [sb, sk] = VBCC(single);
    assert(sb.empty() && sk == vector<int>{0});
    bct.init(single);
    assert(bct.tot == 1 && bct.tree.n == 1 && bct.tree.edges.empty());
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
