#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "graph/eulerian.hpp"

int main() {
    vector<vector<pair<int, int>>> directed(4);
    directed[0].emplace_back(1, 1); directed[1].emplace_back(0, 1);
    assert(isEulerian(directed) == 2 && isEulerianPath(directed) && isEulerianCircuit(directed));
    directed[0].emplace_back(2, 1); directed[2].emplace_back(0, 1);
    assert(isEulerian(directed) == 2 && isEulerian(directed, true, 0) == 2);
    vector<vector<pair<int, int>>> path(4);
    path[0].emplace_back(1, 1); path[1].emplace_back(2, 1);
    assert(isEulerian(path) == 1 && isEulerianPath(path, true, 0));
    assert(!isEulerianPath(path, true, 2) && isEulerian(path, true, 3) == 0);
    path[2].emplace_back(0, 1);
    assert(isEulerianCircuit(path) && isEulerian(path, true, 1) == 2);
    vector<vector<pair<int, int>>> undirected(4);
    auto ue = [&](int u, int v) { undirected[u].emplace_back(v, 0); undirected[v].emplace_back(u, 0); };
    ue(0, 1); ue(1, 2);
    assert(isEulerian(undirected, false) == 1 && isEulerianPath(undirected, false, 0));
    assert(!isEulerianPath(undirected, false, 3));
    ue(2, 0);
    assert(isEulerianCircuit(undirected, false) && isEulerian(undirected, false, 3) == 0);
    undirected[3].emplace_back(3, 0);
    assert(isEulerian(undirected, false) == 0);
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
