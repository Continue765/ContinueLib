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
    SegmentTree<ReverseMono<Mono>> rev;

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
            int u = i;
            if constexpr (edge) {
                u = tree.eToV(i);
            }
            a[tree.in[u]] = init[i];
        }
        seg.init(a);
        rev.init(a);
    }

    void modify(int i, const X& x) {
        int u = i;
        if constexpr (edge) {
            u = tree.eToV(i);
        }
        int p = tree.in[u];
        seg.modify(p, x);
        rev.modify(p, x);
    }

    void apply(int i, const X& x) {
        int u = i;
        if constexpr (edge) {
            u = tree.eToV(i);
        }
        int p = tree.in[u];
        modify(i, Mono::op(seg.rangeQuery(p, p + 1), x));
    }

    X pathQuery(int u, int v) {
        X ans = Mono::e();
        hld.forPath(u, v, edge, [&](int l, int r, bool reversed) {
            X cur = (reversed ? rev.rangeQuery(l, r) : seg.rangeQuery(l, r));
            ans = Mono::op(ans, cur);
        });
        return ans;
    }

    // 非交换运算按原 HLD 序合并；换根边权不支持子树补集。
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
    int maxPath(F&& check, int u, int v) {
        // check 对路径前缀须满足从 true 到 false 的单调性。
        X acc = Mono::e();
        if constexpr (!edge) {
            if (!check(seg.rangeQuery(tree.in[u], tree.in[u] + 1))) {
                return -1;
            }
        } else if (!check(acc)) {
            return -1;
        }

        int ans = v;
        bool done = false;
        hld.forPath(u, v, edge, [&](int l, int r, bool reversed) {
            if (done) {
                return;
            }
            X cur = reversed ? rev.rangeQuery(l, r) : seg.rangeQuery(l, r);
            X next = Mono::op(acc, cur);
            if (check(next)) {
                acc = next;
                return;
            }
            int p = reversed ? rev.minLeft(r, check, acc) - 1
                             : seg.maxRight(l, check, acc);
            int w = tree.seq[p];
            if constexpr (edge) {
                ans = reversed ? w : tree.fa[w];
            } else {
                ans = w == u ? -1 : hld.jump(w, u, 1);
            }
            done = true;
        });
        return ans;
    }

};
