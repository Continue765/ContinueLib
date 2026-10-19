#pragma once
#include <algebra/monoid.hpp>
#include <data_structure/segment_tree/segment_tree.hpp>
#include <graph/tree/hld.hpp>

template <typename T, typename Mono, bool edge = false>
struct TreeMono {
    using X = typename Mono::Type;

    int n;
    HLD<T>& hld;
    Tree<T>& tree;
    SegmentTree<Mono> seg;
    SegmentTree<ReverseMono<Mono>> rseg;

    TreeMono(HLD<T>& hld) : n(hld.tree.n), hld(hld), tree(hld.tree) {
        build(vector<X>(n - edge, Mono::e()));
    }
    TreeMono(HLD<T>& hld, const vector<X>& init) : n(hld.tree.n), hld(hld), tree(hld.tree) {
        build(init);
    }

    void build(const vector<X>& init) {
        assert(int(init.size()) == n - edge);
        vector<X> a(n, Mono::e());
        for (int i = 0; i < int(init.size()); i++) {
            a[id(i)] = init[i];
        }
        seg.init(a);
        rseg.init(a);
    }

    void modify(int i, const X& x) {
        int p = id(i);
        seg.modify(p, x);
        rseg.modify(p, x);
    }

    void apply(int i, const X& x) {
        int p = id(i);
        modify(i, Mono::op(seg.rangeQuery(p, p + 1), x));
    }

    X pathQuery(int u, int v) {
        X ans = Mono::e();
        hld.forPath(u, v, edge, [&](int l, int r, bool rev) {
            X cur = (rev ? rseg.rangeQuery(l, r) : seg.rangeQuery(l, r));
            ans = Mono::op(ans, cur);
        });
        return ans;
    }

    X subtreeQuery(int u, int root = -1) {
        if (root == -1) {
            root = tree.root;
        }
        if (root == u) {
            return seg.rangeQuery(0, n);
        }
        if (!hld.isAncester(u, root)) {
            return seg.rangeQuery(tree.in[u] + edge, tree.out[u]);
        }
        assert(!edge);
        int v = hld.jump(root, tree.dep[root] - tree.dep[u] - 1);
        return Mono::op(seg.rangeQuery(0, tree.in[v]), seg.rangeQuery(tree.out[v], n));
    }

    X allQuery() {
        return seg.rangeQuery(0, n);
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
            X cur = rev ? rseg.rangeQuery(l, r) : seg.rangeQuery(l, r);
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
