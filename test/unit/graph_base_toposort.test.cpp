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
    Digraph<int> empty;
    assert(empty.n == 0 && empty.edges.empty() && empty.adj.empty());
    assert(toposort(empty).empty() && lexMinToposort(empty).empty());
    Digraph<int> original(4);
    original.add(3, 1, 8); original.add(1, 3, 4);
    original.add(3, 3, 7); original.add(0, 3, 2);
    original.add(3, 1, 9);
    auto sub = induced(original, vector<int>{3, 1, 2});
    assert(sub.n == 3 && sub.edges.size() == 4);
    vector<tuple<int, int, int>> got;
    for (auto [u, v, w] : sub.edges) got.emplace_back(u, v, w);
    assert((got == vector<tuple<int, int, int>>{{0, 1, 8}, {1, 0, 4}, {0, 0, 7}, {0, 1, 9}}));
    auto ug = toUndigraph(sub);
    assert(ug.n == sub.n && ug.edges.size() == sub.edges.size());
    for (int id = 0; id < int(sub.edges.size()); id++) {
        auto [u, v, w] = sub.edges[id];
        auto e = ug.edges[id];
        assert(e.u == u && e.v == v && e.w == w);
        assert(count(ug.adj[u].begin(), ug.adj[u].end(), pair{v, id}) == (u == v ? 2 : 1));
    }
    assert((degree(ug) == vector<int>{5, 3, 0}));
    auto [in, out] = degree(sub);
    assert((in == vector<int>{2, 2, 0} && out == vector<int>{3, 1, 0}));
    auto nothing = induced(ug, vector<int>{});
    assert(nothing.n == 0 && nothing.edges.empty());
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
