#pragma once
#include <random/array.hpp>

vector<pair<int, int>> randGraph(int n, int m) {
    set<pair<int, int>> s;
    while (m > int(s.size())) {
        int u = randInt(n), v = randInt(n);
        if (u != v) {
            s.emplace(u, v);
        }
    }
    vector<pair<int, int>> e(s.begin(), s.end());
    shuffle(e);
    return e;
}

vector<pair<int, int>> randTree(int n) {
    auto p = randPerm(n);
    vector<pair<int, int>> e;
    for (int i = 1; i < n; i++) {
        e.emplace_back(p[randInt(i)], p[i]);
    }
    shuffle(e);
    return e;
}

vector<pair<int, int>> randChain(int n) {
    auto p = randPerm(n);
    vector<pair<int, int>> e;
    for (int i = 1; i < n; i++) {
        e.emplace_back(p[i - 1], p[i]);
    }
    shuffle(e);
    return e;
}

vector<pair<int, int>> randStar(int n) {
    auto p = randPerm(n);
    vector<pair<int, int>> e;
    for (int i = 1; i < n; i++) {
        e.emplace_back(p[0], p[i]);
    }
    shuffle(e);
    return e;
}

vector<pair<int, int>> randConnectedGraph(int n, int m) {
    set<pair<int, int>> s;
    for (auto [u, v] : randTree(n)) {
        s.emplace(min(u, v), max(u, v));
    }
    while (m > int(s.size())) {
        int u = randInt(n), v = randInt(n);
        if (u > v) {
            swap(u, v);
        }
        if (u != v) {
            s.emplace(u, v);
        }
    }
    vector<pair<int, int>> e(s.begin(), s.end());
    for (auto& [u, v] : e) {
        if (randBool()) {
            swap(u, v);
        }
    }
    shuffle(e);
    return e;
}

vector<pair<int, int>> randDAG(int n, int m) {
    auto p = randPerm(n);
    set<pair<int, int>> s;
    while (m > int(s.size())) {
        int u = randInt(n), v = randInt(n);
        if (u < v) {
            s.emplace(u, v);
        }
    }
    vector<pair<int, int>> e;
    for (auto [u, v] : s) {
        e.emplace_back(p[u], p[v]);
    }
    shuffle(e);
    return e;
}

vector<pair<int, int>> randBipartiteGraph(int n, int k, int m) {
    set<pair<int, int>> s;
    while (m > int(s.size())) {
        s.emplace(randInt(n), n + randInt(k));
    }
    vector<pair<int, int>> e(s.begin(), s.end());
    shuffle(e);
    return e;
}

vector<pair<int, int>> randSCC(int n, int m) {
    auto p = randPerm(n);
    set<pair<int, int>> s;
    if (n > 1)
        for (int i = 0; i < n; i++)
            s.emplace(p[i], p[(i + 1) % n]);
    while (m > int(s.size())) {
        int u = randInt(n), v = randInt(n);
        if (u != v) {
            s.emplace(u, v);
        }
    }
    vector<pair<int, int>> e(s.begin(), s.end());
    shuffle(e);
    return e;
}
