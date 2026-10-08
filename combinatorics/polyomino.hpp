#pragma once
#include <common.hpp>

struct Polyomino {
    using Cell = pair<int, int>;
    set<Cell> cells;
    Polyomino() {}
    Polyomino(const set<Cell>& cells_) : cells(cells_) {}
};

Polyomino normalize(const Polyomino& p) {
    if (p.cells.empty()) {
        return p;
    }
    int minX = p.cells.begin()->first;
    int minY = p.cells.begin()->second;
    for (auto& [x, y] : p.cells) {
        minX = min(minX, x);
        minY = min(minY, y);
    }
    Polyomino res;
    for (auto& [x, y] : p.cells) {
        res.cells.emplace(x - minX, y - minY);
    }
    return res;
}

Polyomino rotate(const Polyomino& p) {
    Polyomino res;
    for (auto& [x, y] : p.cells) {
        res.cells.emplace(y, -x);
    }
    return normalize(res);
}

Polyomino flip(const Polyomino& p) {
    Polyomino res;
    for (auto& [x, y] : p.cells) {
        res.cells.emplace(x, -y);
    }
    return normalize(res);
}