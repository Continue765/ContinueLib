#pragma once
#include <algebra/monoid.hpp>
#include <data_structure/segment_tree/segment_tree.hpp>
#include <graph/tree/hld.hpp>

template <typename T, typename Mono, bool edge = false>
struct TreeMono {
    using X = typename Mono::Type;

    HLD<T>& hld;
    Tree<T>& tree;
    int n;
    SegmentTree<Mono> seg;
    SegmentTree<RevMono<Mono>> rseg;

    TreeMono(HLD<T>& hld_) : TreeMono(hld_, vector<X>(hld_.tree.n - edge, Mono::e())) {}
    TreeMono(HLD<T>& hld_, const vector<X>& init) : hld(hld_), tree(hld.tree), n(tree.n) {
        assert(int(init.size()) == n - edge);
        vector<X> a(n, Mono::e());
        for (int i = 0; i < int(init.size()); i++) {
            a[id(i)] = init[i];
        }
        seg = SegmentTree<Mono>(a);
        rseg = SegmentTree<RevMono<Mono>>(a);
    }

    void modify(int i, const X& x) {
        int p = id(i);
        seg.modify(p, x);
        rseg.modify(p, x);
    }

    void apply(int i, const X& x) {
        int p = id(i);
        modify(i, Mono::op(seg.query(p, p + 1), x));
    }

    X pathQuery(int u, int v) {
        X ans = Mono::e();
        hld.forPath(u, v, edge, [&](int l, int r, bool rev) {
            X cur = (rev ? rseg.query(l, r) : seg.query(l, r));
            ans = Mono::op(ans, cur);
        });
        return ans;
    }

    X subtreeQuery(int u, int root = -1) {
        if (root == -1) {
            root = tree.root;
        }
        if (root == u) {
            return seg.query(0, n);
        }
        if (!hld.isAncester(u, root)) {
            return seg.query(tree.in[u] + edge, tree.out[u]);
        }
        assert(!edge);
        int v = hld.jump(root, tree.dep[root] - tree.dep[u] - 1);
        return Mono::op(seg.query(0, tree.in[v]), seg.query(tree.out[v], n));
    }

    X allQuery() {
        return seg.query(0, n);
    }

    template <typename F>
    int maxPath(F&& pred, int u, int v) {
        X acc = Mono::e();
        if (edge && !pred(acc)) {
            return -1;
        }

        int ans = v;
        bool done = false;
        hld.forPath(u, v, edge, [&](int l, int r, bool rev) {
            if (done) {
                return;
            }
            X cur = rev ? rseg.query(l, r) : seg.query(l, r);
            X next = Mono::op(acc, cur);
            if (pred(next)) {
                acc = next;
                return;
            }
            int p = (rev ? rseg.minLeft(r, pred, acc) - 1 : seg.maxRight(l, pred, acc));
            int w = tree.seq[p];
            if constexpr (edge) {
                ans = (rev ? w : tree.fa[w]);
            } else {
                ans = (w == u ? -1 : hld.jump(w, u, 1));
            }
            done = true;
        });
        return ans;
    }

    int id(int i) {
        int u = (edge ? tree.eToV(i) : i);
        return tree.in[u];
    }
};