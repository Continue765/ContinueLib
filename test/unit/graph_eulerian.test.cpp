#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "graph/eulerian.hpp"

template <bool Directed>
void checkWalk(Graph<int, Directed>& g, int start = -1) {
    auto [vs, es] = findEulerian(g, start);
    int m = g.edges.size();
    assert(int(vs.size()) == m + 1 && int(es.size()) == m);
    if (start != -1) assert(vs.front() == start);
    vector<int> seen(m);
    for (int i = 0; i < m; ++i) {
        int id = es[i];
        assert(0 <= id && id < m && !seen[id]++);
        auto e = g.edges[id];
        bool ok = e.u == vs[i] && e.v == vs[i + 1];
        if constexpr (!Directed) ok |= e.v == vs[i] && e.u == vs[i + 1];
        assert(ok);
    }
}

int main() {
    Digraph<int> directed(4);
    directed.add(0, 1); directed.add(1, 0);
    assert(isEulerian(directed) == 2 && isEulerianPath(directed) && isEulerianCircuit(directed));
    directed.add(0, 2); directed.add(2, 0);
    assert(isEulerian(directed, 0) == 2);
    checkWalk(directed);
    checkWalk(directed, 2);
    Digraph<int> path(4);
    path.add(0, 1); path.add(1, 2);
    assert(isEulerian(path) == 1 && isEulerianPath(path, 0));
    assert(!isEulerianPath(path, 2) && isEulerian(path, 3) == 0);
    checkWalk(path);
    checkWalk(path, 0);
    assert(findEulerian(path, 2).first.empty());
    path.add(2, 0);
    assert(isEulerianCircuit(path) && isEulerian(path, 1) == 2);
    checkWalk(path, 1);

    Undigraph<int> undirected(4);
    undirected.add(0, 1); undirected.add(1, 2);
    assert(isEulerian(undirected) == 1 && isEulerianPath(undirected, 0));
    assert(!isEulerianPath(undirected, 3));
    checkWalk(undirected);
    checkWalk(undirected, 2);
    undirected.add(2, 0);
    assert(isEulerianCircuit(undirected) && isEulerian(undirected, 3) == 0);
    checkWalk(undirected);
    undirected.add(3, 3);
    assert(isEulerian(undirected) == 0);
    assert(findEulerian(undirected).first.empty());

    Undigraph<int> parallel(2);
    parallel.add(0, 1, 9); parallel.add(0, 1, 3); parallel.add(0, 0, 5);
    assert(isEulerianCircuit(parallel));
    checkWalk(parallel);
    Digraph<int> directedParallel(2);
    directedParallel.add(0, 1); directedParallel.add(0, 1);
    directedParallel.add(1, 0); directedParallel.add(0, 0);
    assert(isEulerian(directedParallel) == 1);
    checkWalk(directedParallel);
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
