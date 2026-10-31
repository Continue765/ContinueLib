#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "graph/components/scc.hpp"
#include "graph/components/ebcc.hpp"
#include "graph/components/block_cut_tree.hpp"

int main() {
    Digraph<int> directed(5);
    directed.add(0, 1); directed.add(1, 0); directed.add(1, 2);
    directed.add(2, 3); directed.add(3, 2);
    auto [cnt, id] = SCC(directed);
    assert(cnt == 3 && id[0] == id[1] && id[2] == id[3]);
    assert(id[0] < id[2] && id[4] != id[0] && id[4] != id[2]);
    assert(SCC(directed) == make_pair(cnt, id));
    Digraph<int> dag(2);
    dag.add(0, 1);
    auto [dc, di] = SCC(dag);
    assert(dc == 2 && di[0] < di[1]);

    Undigraph<int> g(5);
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
    Undigraph<int> parallel(3);
    parallel.add(0, 1, 8); parallel.add(0, 1, 3); parallel.add(1, 2, 5);
    auto [pc, pi] = EBCC(parallel);
    assert(pc == 2 && pi[0] == pi[1] && pi[1] != pi[2]);
    bct = BlockCutTree(parallel);
    assert(bct.n == 3 && bct.tot == 5 && bct.isCut(1));
    assert(!bct.isCut(0) && !bct.isCut(2));
    assert(bct.tree.edges.size() == 4);
    assert(bct.tree[3].size() == 2 && bct.tree[4].size() == 2);
    Undigraph<int> single(1);
    auto [sc, si] = EBCC(single);
    assert(sc == 1 && si == vector<int>{0});
    bct = BlockCutTree(single);
    assert(bct.tot == 1 && bct.tree.n == 1 && bct.tree.edges.empty());
    assert(!bct.isCut(0));

    // 自环忽略，重边只贡献一次点双关联。
    Undigraph<int> loops(2);
    loops.add(0, 0);
    loops.add(0, 1);
    loops.add(0, 0);
    bct = BlockCutTree(loops);
    assert(bct.tot == 3 && bct.tree.edges.size() == 2);
    assert(!bct.isCut(0) && !bct.isCut(1));
    assert(bct.tree[2].size() == 2);

    Undigraph<int> onlyLoops(1);
    onlyLoops.add(0, 0);
    onlyLoops.add(0, 0);
    bct = BlockCutTree(onlyLoops);
    assert(bct.tot == 1 && bct.tree.edges.empty() && !bct.isCut(0));

    // 非连通图中分别处理 DFS 根的割点判定。
    Undigraph<int> forest(7);
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

    bct = BlockCutTree(Undigraph<int>(0));
    assert(bct.n == 0 && bct.tot == 0 && bct.tree.n == 0);
    assert(bct.tree.edges.empty());
    mt19937 rng(57115);
    for (int it = 0; it < 500; it++) {
        int n = 1 + rng() % 8;
        Digraph<int> dg(n);
        Undigraph<int> ug(n);
        vector<vector<bool>> reach(n, vector<bool>(n));
        for (int u = 0; u < n; u++) reach[u][u] = true;
        for (int j = 0, m = rng() % 20; j < m; j++) {
            int u = rng() % n, v = rng() % n;
            dg.add(u, v); ug.add(u, v);
            reach[u][v] = true;
        }
        for (int k = 0; k < n; k++) for (int u = 0; u < n; u++) for (int v = 0; v < n; v++) {
            reach[u][v] = reach[u][v] || (reach[u][k] && reach[k][v]);
        }
        auto [cnt, id] = SCC(dg);
        set<int> labels(id.begin(), id.end());
        assert(int(labels.size()) == cnt);
        for (int u = 0; u < n; u++) for (int v = 0; v < n; v++) {
            assert((id[u] == id[v]) == (reach[u][v] && reach[v][u]));
            if (reach[u][v] && id[u] != id[v]) assert(id[u] < id[v]);
        }
        auto components = [&](int bannedVertex, int bannedEdge, const vector<bool>& bridges) {
            vector<int> label(n, -1);
            int count = 0;
            for (int s = 0; s < n; s++) if (s != bannedVertex && label[s] == -1) {
                vector<int> q{s};
                label[s] = count++;
                for (int i = 0; i < int(q.size()); i++) for (auto [v, eid] : ug[q[i]]) {
                    if (v == bannedVertex || eid == bannedEdge || (!bridges.empty() && bridges[eid]) || label[v] != -1) continue;
                    label[v] = label[s];
                    q.push_back(v);
                }
            }
            return pair{count, label};
        };
        int base = components(-1, -1, {}).first;
        vector<bool> bridges(ug.edges.size());
        for (int eid = 0; eid < int(ug.edges.size()); eid++) bridges[eid] = components(-1, eid, {}).first > base;
        auto [ec, eb] = EBCC(ug);
        auto [expectedCount, expected] = components(-1, -1, bridges);
        assert(ec == expectedCount);
        for (int u = 0; u < n; u++) for (int v = 0; v < n; v++) assert((eb[u] == eb[v]) == (expected[u] == expected[v]));
        BlockCutTree bct(ug);
        for (int u = 0; u < n; u++) assert(bct.isCut(u) == (components(u, -1, {}).first > base));
    }
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
