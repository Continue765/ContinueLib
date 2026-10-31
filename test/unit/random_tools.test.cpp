#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <random/graph.hpp>
#include <random/simulated_annealing.hpp>

void testBase() {
    rng.seed(7654321);
    vector<i64> first;
    for (int i = 0; i < 100; i++) first.push_back(randInt(-100, 101));
    rng.seed(7654321);
    for (i64 x : first) assert(randInt(-100, 101) == x);
    array<int, 2> count{};
    for (int i = 0; i < 1000; i++) {
        i64 x = randInt(-17, 23);
        assert(-17 <= x && x < 23);
        assert(randInt(-5, -4) == -5);
        assert(randInt(1) == 0);
        assert(randInt(37) < 37);
        count[randBool()]++;
        double y = randReal(-2.5, 3.5);
        assert(-2.5 <= y && y < 3.5);
    }
    assert(count[0] && count[1]);
}

void testArray() {
    for (int n = 0; n <= 40; n++) {
        auto p = randPerm(n);
        auto sorted = p;
        ranges::sort(sorted);
        for (int i = 0; i < n; i++) assert(sorted[i] == i);
        shuffle(p);
        auto after = p;
        ranges::sort(after);
        assert(after == sorted);
        auto a = randArray(n, -7, 8);
        assert(int(a.size()) == n);
        for (i64 x : a) assert(-7 <= x && x < 8);
        for (int span : {max(n, 1), n + 3, n + 100}) {
            auto distinct = randDistinct(n, -31, -31 + span);
            assert(int(distinct.size()) == n);
            assert(int(set<i64>(distinct.begin(), distinct.end()).size()) == n);
            for (i64 x : distinct) assert(-31 <= x && x < -31 + span);
        }
    }
    vector<int> a{4, 4, 9, 17};
    for (int i = 0; i < 100; i++) {
        int& x = randElem(a);
        int index = &x - a.data();
        assert(0 <= index && index < int(a.size()));
        x = i;
        assert(a[index] == i);
    }
    vector<int> single{7};
    assert(&randElem(single) == &single[0]);
}

using Edges = vector<pair<int, int>>;

void checkEdges(int n, int m, const Edges& edges, bool undirected = false) {
    assert(int(edges.size()) == m);
    set<pair<int, int>> seen;
    for (auto [u, v] : edges) {
        assert(0 <= u && u < n && 0 <= v && v < n && u != v);
        if (undirected && u > v) swap(u, v);
        assert(seen.emplace(u, v).second);
    }
}

void checkConnected(int n, const Edges& edges, bool undirected) {
    vector<vector<int>> adj(n);
    for (auto [u, v] : edges) {
        adj[u].push_back(v);
        if (undirected) adj[v].push_back(u);
    }
    for (int source = 0; source < (undirected ? 1 : n); source++) {
        vector<bool> seen(n);
        vector<int> q{source};
        seen[source] = true;
        for (int i = 0; i < int(q.size()); i++) {
            for (int v : adj[q[i]]) {
                if (!seen[v]) seen[v] = true, q.push_back(v);
            }
        }
        assert(int(q.size()) == n);
    }
}

void testGraph() {
    assert(randGraph(0, 0).empty());
    assert(randPerm(0).empty() && randTree(0).empty());
    assert(randChain(0).empty() && randStar(0).empty());
    assert(randDAG(0, 0).empty() && randSCC(0, 0).empty());
    for (int n = 1; n <= 12; n++) {
        for (int it = 0; it < 12; it++) {
            for (auto edges : {randTree(n), randChain(n), randStar(n)}) {
                checkEdges(n, n - 1, edges, true);
                checkConnected(n, edges, true);
            }
            auto chain = randChain(n);
            auto star = randStar(n);
            vector<int> chainDegree(n), starDegree(n);
            for (auto [u, v] : chain) chainDegree[u]++, chainDegree[v]++;
            for (auto [u, v] : star) starDegree[u]++, starDegree[v]++;
            if (n > 1) {
                assert(ranges::count(chainDegree, 1) == 2);
                assert(*ranges::max_element(chainDegree) <= 2);
                assert(*ranges::max_element(starDegree) == n - 1);
            }
            int directedMax = n * (n - 1), undirectedMax = directedMax / 2;
            for (int m : {0, directedMax / 2, directedMax}) {
                checkEdges(n, m, randGraph(n, m));
            }
            for (int m : {n - 1, (n - 1 + undirectedMax) / 2, undirectedMax}) {
                auto edges = randConnectedGraph(n, m);
                checkEdges(n, m, edges, true);
                checkConnected(n, edges, true);
            }
            for (int m : {0, undirectedMax / 2, undirectedMax}) {
                auto edges = randDAG(n, m);
                checkEdges(n, m, edges);
                vector<vector<int>> adj(n);
                vector<int> deg(n), q;
                for (auto [u, v] : edges) adj[u].push_back(v), deg[v]++;
                for (int u = 0; u < n; u++) if (!deg[u]) q.push_back(u);
                for (int i = 0; i < int(q.size()); i++) {
                    for (int v : adj[q[i]]) if (!--deg[v]) q.push_back(v);
                }
                assert(int(q.size()) == n);
            }
            int minimum = n == 1 ? 0 : n;
            for (int m : {minimum, (minimum + directedMax) / 2, directedMax}) {
                auto edges = randSCC(n, m);
                checkEdges(n, m, edges);
                checkConnected(n, edges, false);
            }
            int k = 1 + it % 5;
            for (int m : {0, n * k / 2, n * k}) {
                auto edges = randBipartiteGraph(n, k, m);
                checkEdges(n + k, m, edges);
                for (auto [u, v] : edges) assert(u < n && n <= v);
            }
        }
    }
    assert(randBipartiteGraph(0, 0, 0).empty());
}

void testAnnealing() {
    int calls = 0;
    double last = 2;
    auto best = simulatedAnnealing(5, [](int x) { return x; },
        [&](int cur, double t) {
            assert(0.01 <= t && t <= 1 && t <= last);
            last = t;
            calls++;
            return cur + 1;
        }, 1, 0.01, 0.01);
    assert(calls > 0 && best == 5 + calls);

    calls = 0;
    int bestSeen = 7;
    auto score = [](const pair<int, int>& x) { return x.first; };
    auto state = simulatedAnnealing(pair{7, 0}, score,
        [&](const pair<int, int>& cur, double) {
            // 极低温下拒绝严格劣解，同时保留历史最佳状态。
            assert(cur.first == bestSeen);
            int next = calls++ % 2 == 0 ? bestSeen + 1 : bestSeen - 1000;
            bestSeen = max(bestSeen, next);
            return pair{next, calls};
        }, 1e-6, 1e-9, 0.01);
    assert(calls > 0 && state.first == bestSeen);
    assert(state.second % 2 == 1);

    calls = 0;
    int previous = 10;
    auto retained = simulatedAnnealing(10, [](int x) { return x; },
        [&](int cur, double) {
            // 足够高的温度令 exp(-1 / t) 舍入为 1，劣解也会被接受。
            assert(cur == previous);
            calls++;
            return --previous;
        }, 1e100, 1e90, 0.01);
    assert(calls > 0 && retained == 10);
}

int main() {
    testBase();
    testArray();
    testGraph();
    testAnnealing();
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
