#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "graph/components/scc.hpp"
#include "graph/components/ebcc.hpp"
#include "graph/components/vbcc.hpp"
#include "graph/components/block_cut_tree.hpp"

int main() {
    SCC scc(5);
    scc.addEdge(0, 1); scc.addEdge(1, 0); scc.addEdge(1, 2); scc.addEdge(2, 3); scc.addEdge(3, 2);
    auto id = scc.work();
    assert(id[0] == id[1] && id[2] == id[3] && id[0] < id[2] && id[4] != id[0]);
    scc.init(2); scc.addEdge(0, 1); id = scc.work();
    assert(id.size() == 2 && id[0] < id[1]);
    EBCC ebcc(5);
    ebcc.addEdge(0, 1); ebcc.addEdge(1, 2); ebcc.addEdge(2, 0); ebcc.addEdge(2, 3);
    auto eb = ebcc.work();
    assert(eb[0] == eb[1] && eb[1] == eb[2] && eb[2] != eb[3] && eb[4] != eb[3]);
    ebcc.init(1); assert(ebcc.work() == vector<int>{0});
    VBCC vbcc(5);
    vbcc.addEdge(0, 1); vbcc.addEdge(1, 2); vbcc.addEdge(2, 0); vbcc.addEdge(2, 3);
    vbcc.work();
    assert(vbcc.cut[2] && !vbcc.cut[0] && vbcc.comp.size() == 2);
    assert(vbcc.edges.size() == 4);
    vbcc.init(1);
    vbcc.work();
    assert(vbcc.comp.empty() && vbcc.cut == vector<int>{0});
    BlockCutTree bct(5);
    bct.addEdge(0, 1); bct.addEdge(1, 2); bct.addEdge(2, 0); bct.addEdge(2, 3);
    bct.build();
    assert(bct.cut[2] && !bct.cut[0] && bct.comp.size() == 2);
    assert(bct.tot == 7 && bct.tree[2].size() == 2);
    bct.init(2); bct.addEdge(0, 1); bct.build();
    assert(bct.tot == 3 && bct.comp.size() == 1 && bct.edges.size() == 1);
    bct.init(1); bct.build();
    assert(bct.tot == 1 && bct.tree.size() == 1 && bct.comp.empty());
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
