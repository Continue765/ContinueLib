#pragma once
#include <common.hpp>

template <typename ActMono>
struct DynamicSegmentTree {
    using Mono = typename ActMono::Mono;
    using Tag = typename ActMono::Tag;
    using X = typename ActMono::X;
    using Y = typename ActMono::Y;

    int n;
    int root;
    vector<X> info;
    vector<Y> tag;
    vector<int> lc, rc;

    DynamicSegmentTree() : n(0), root(-1) {}
    DynamicSegmentTree(int n_) : n(n_), root(-1) {
        root = newNode();
    }
    DynamicSegmentTree(const vector<X>& init) : n(init.size()), root(-1) {
        auto build = [&](auto&& self, int l, int r) -> int {
            int p = newNode();
            if (r - l == 1) {
                info[p] = init[l];
                return p;
            }
            int mid = (l + r) / 2;
            lc[p] = self(self, l, mid);
            rc[p] = self(self, mid, r);
            pull(p);
            return p;
        };
        root = build(build, 0, n);
    }

    int newNode() {
        info.push_back(Mono::e());
        tag.push_back(Tag::e());
        lc.push_back(-1);
        rc.push_back(-1);
        return int(info.size()) - 1;
    }

    void pull(int p) {
        info[p] = Mono::op(info[lc[p]], info[rc[p]]);
    }

    void update(int p, int len, const Y& v) {
        info[p] = ActMono::act(info[p], v, len);
        tag[p] = Tag::op(tag[p], v);
    }

    void push(int p, int len) {
        if (lc[p] == -1) {
            lc[p] = newNode();
        }
        if (rc[p] == -1) {
            rc[p] = newNode();
        }
        update(lc[p], len / 2, tag[p]);
        update(rc[p], (len + 1) / 2, tag[p]);
        tag[p] = Tag::e();
    }

    void modify(int p, int l, int r, int x, const X& v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int mid = (l + r) / 2;
        push(p, r - l);
        if (x < mid) {
            modify(lc[p], l, mid, x, v);
        } else {
            modify(rc[p], mid, r, x, v);
        }
        pull(p);
    }
    void modify(int x, const X& v) {
        modify(root, 0, n, x, v);
    }

    X query(int p, int l, int r, int x, int y) {
        if (y <= l || r <= x) {
            return Mono::e();
        }
        if (x <= l && r <= y) {
            return info[p];
        }
        int mid = (l + r) / 2;
        push(p, r - l);
        return Mono::op(query(lc[p], l, mid, x, y), query(rc[p], mid, r, x, y));
    }
    X query(int l, int r) {
        return query(root, 0, n, l, r);
    }

    void apply(int p, int l, int r, int x, int y, const Y& v) {
        if (y <= l || r <= x) {
            return;
        }
        if (x <= l && r <= y) {
            update(p, r - l, v);
            return;
        }
        int mid = (l + r) / 2;
        push(p, r - l);
        apply(lc[p], l, mid, x, y, v);
        apply(rc[p], mid, r, x, y, v);
        pull(p);
    }
    void apply(int l, int r, const Y& v) {
        apply(root, 0, n, l, r, v);
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
        push(p, r - l);
        int res = findFirst(lc[p], l, mid, x, y, pred);
        if (res == -1) {
            res = findFirst(rc[p], mid, r, x, y, pred);
        }
        return res;
    }
    template <typename F>
    int findFirst(int l, int r, F&& pred) {
        return findFirst(root, 0, n, l, r, pred);
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
        push(p, r - l);
        int res = findLast(rc[p], mid, r, x, y, pred);
        if (res == -1) {
            res = findLast(lc[p], l, mid, x, y, pred);
        }
        return res;
    }
    template <typename F>
    int findLast(int l, int r, F&& pred) {
        return findLast(root, 0, n, l, r, pred);
    }

    template <typename F>
    int maxRight(int l, F&& pred, X& sum) {
        int p = findFirst(l, n, [&](const X& x) {
            X v = Mono::op(sum, x);
            if (!pred(v)) {
                return true;
            }
            sum = v;
            return false;
        });
        return p == -1 ? n : p;
    }

    template <typename F>
    int minLeft(int r, F&& pred, X& sum) {
        int p = findLast(0, r, [&](const X& x) {
            X v = Mono::op(x, sum);
            if (!pred(v)) {
                return true;
            }
            sum = v;
            return false;
        });
        return p + 1;
    }
};