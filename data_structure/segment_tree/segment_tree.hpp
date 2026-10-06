#pragma once
#include <common.hpp>

template <typename Mono>
struct SegmentTree {
    using X = typename Mono::Type;

    int n;
    vector<X> info;

    SegmentTree() : n(0) {}
    SegmentTree(const vector<X>& init_) {
        init(init_);
    }

    void init(const vector<X>& init_) {
        n = init_.size();
        int logn = __lg(n);
        info.assign(4 << logn, Mono::e());

        auto build = [&](auto&& self, int p, int l, int r) -> void {
            if (r - l == 1) {
                info[p] = init_[l];
                return;
            }
            int mid = (l + r) / 2;
            self(self, 2 * p, l, mid);
            self(self, 2 * p + 1, mid, r);
            pull(p);
        };

        build(build, 1, 0, n);
    }

    void pull(int p) {
        info[p] = Mono::op(info[2 * p], info[2 * p + 1]);
    }

    void modify(int p, int l, int r, int x, const X& v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int mid = (l + r) / 2;
        if (x < mid) {
            modify(2 * p, l, mid, x, v);
        } else {
            modify(2 * p + 1, mid, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const X& v) {
        modify(1, 0, n, p, v);
    }

    X rangeQuery(int p, int l, int r, int x, int y) {
        if (y <= l || r <= x) {
            return Mono::e();
        }
        if (x <= l && r <= y) {
            return info[p];
        }
        int mid = (l + r) / 2;
        return Mono::op(rangeQuery(2 * p, l, mid, x, y), rangeQuery(2 * p + 1, mid, r, x, y));
    }
    X rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }

    template <typename F>
    int findFirst(int p, int l, int r, int x, int y, F&& pred) {
        if (y <= l || r <= x) {
            return -1;
        }
        if (x <= l && r <= y && !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int mid = (l + r) / 2;
        int res = findFirst(2 * p, l, mid, x, y, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, mid, r, x, y, pred);
        }
        return res;
    }
    template <typename F>
    int findFirst(int l, int r, F&& pred) {
        return findFirst(1, 0, n, l, r, pred);
    }

    template <typename F>
    int findLast(int p, int l, int r, int x, int y, F&& pred) {
        if (y <= l || r <= x) {
            return -1;
        }
        if (x <= l && r <= y && !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int mid = (l + r) / 2;
        int res = findLast(2 * p + 1, mid, r, x, y, pred);
        if (res == -1) {
            res = findLast(2 * p, l, mid, x, y, pred);
        }
        return res;
    }
    template <typename F>
    int findLast(int l, int r, F&& pred) {
        return findLast(1, 0, n, l, r, pred);
    }
};