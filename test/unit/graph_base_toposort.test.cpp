#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "graph/graph.hpp"
#include "graph/toposort.hpp"

int main() {
    Digraph<int> graph(4);
    graph.add(0, 1, 3);
    graph.add(0, 2, 5);
    graph.add(1, 3, 7);
    assert(graph.n == 4);
    assert(graph.edges.size() == 3);
    assert(((graph.adj[0][1] == pair<int, int>(2, 1))));
    auto topo = toposort(graph);
    vector<int> pos(4);
    for (int i = 0; i < 4; ++i) pos[topo[i]] = i;
    assert(pos[0] < pos[1] && pos[0] < pos[2] && pos[1] < pos[3]);
    assert((lexMinToposort(graph) == vector<int>{0, 1, 2, 3}));
    graph.add(3, 0);
    assert(toposort(graph).empty());
    assert(lexMinToposort(graph).empty());
    auto reversed = reverse(graph);
    assert(reversed.n == graph.n && reversed.edges.size() == graph.edges.size());
    for (int id = 0; id < int(graph.edges.size()); ++id) {
        auto e = graph.edges[id], r = reversed.edges[id];
        assert(r.u == e.v && r.v == e.u && r.w == e.w);
    }
    Undigraph<int> undirected(2);
    assert(undirected.add(0, 1, 8) == 0);
    assert(undirected.add(0, 1) == 1);
    assert(undirected.edges.size() == 2 && undirected.edges[1].w == 1);
    assert((undirected.adj[0] == vector<pair<int, int>>{{1, 0}, {1, 1}}));
    assert((undirected.adj[1] == vector<pair<int, int>>{{0, 0}, {0, 1}}));
    Digraph<int> parallel(3);
    parallel.add(0, 1, 9); parallel.add(0, 1, 2); parallel.add(1, 2);
    assert((toposort(parallel) == vector<int>{0, 1, 2}));
    assert((lexMinToposort(parallel) == vector<int>{0, 1, 2}));
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
