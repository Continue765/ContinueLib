#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "graph/components/scc.hpp"
#include "graph/components/ebcc.hpp"
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
    BlockCutTree bct(g);
    assert(bct.isCut(2) && !bct.isCut(0));
    for (int u = 0; u < g.n; u++) {
        assert(bct.isCut(u) == (u == 2));
    }
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
    bct = BlockCutTree(parallel);
    assert(bct.n == 3 && bct.tot == 5 && bct.isCut(1));
    assert(!bct.isCut(0) && !bct.isCut(2));
    assert(bct.tree.edges.size() == 4);
    assert(bct.tree[3].size() == 2 && bct.tree[4].size() == 2);
    Graph<int, false> single(1);
    auto [sc, si] = EBCC(single);
    assert(sc == 1 && si == vector<int>{0});
    bct = BlockCutTree(single);
    assert(bct.tot == 1 && bct.tree.n == 1 && bct.tree.edges.empty());
    assert(!bct.isCut(0));

    // 自环忽略，重边只贡献一次点双关联。
    Graph<int, false> loops(2);
    loops.add(0, 0);
    loops.add(0, 1);
    loops.add(0, 0);
    bct = BlockCutTree(loops);
    assert(bct.tot == 3 && bct.tree.edges.size() == 2);
    assert(!bct.isCut(0) && !bct.isCut(1));
    assert(bct.tree[2].size() == 2);

    Graph<int, false> onlyLoops(1);
    onlyLoops.add(0, 0);
    onlyLoops.add(0, 0);
    bct = BlockCutTree(onlyLoops);
    assert(bct.tot == 1 && bct.tree.edges.empty() && !bct.isCut(0));

    // 非连通图中分别处理 DFS 根的割点判定。
    Graph<int, false> forest(7);
    forest.add(0, 1);
    forest.add(0, 2);
    forest.add(3, 4);
    forest.add(4, 5);
    bct = BlockCutTree(forest);
    for (int u = 0; u < forest.n; u++) {
        assert(bct.isCut(u) == (u == 0 || u == 4));
    }
    assert(bct.tot == 11 && bct.tree.edges.size() == 8);
    assert(bct.tree[6].empty());

    bct = BlockCutTree(Graph<int, false>(0));
    assert(bct.n == 0 && bct.tot == 0 && bct.tree.n == 0);
    assert(bct.tree.edges.empty());
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
