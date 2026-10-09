#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "graph/base.hpp"
#include "graph/toposort.hpp"

int main() {
    Graph<int> graph(4);
    graph.addEdge(0, 1, 3);
    graph.addEdge(0, 2, 5);
    graph.addEdge(1, 3, 7);
    assert(graph.n == 4);
    assert(graph.edges.size() == 3);
    assert(((graph.adj[0][1] == pair<int, int>(2, 5))));
    auto topo = toposort(graph.adj);
    vector<int> pos(4);
    for (int i = 0; i < 4; ++i) pos[topo[i]] = i;
    assert(pos[0] < pos[1] && pos[0] < pos[2] && pos[1] < pos[3]);
    assert((lexMinToposort(graph.adj) == vector<int>{0, 1, 2, 3}));
    graph.adj[3].emplace_back(0, 0);
    assert(toposort(graph.adj).empty());
    assert(lexMinToposort(graph.adj).empty());
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
