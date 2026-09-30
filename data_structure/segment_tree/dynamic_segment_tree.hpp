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
    DynamicSegmentTree(int n_) {
        init(n_);
    }

    void init(int n_) {
        n = n_;
        info.clear();
        tag.clear();
        lc.clear();
        rc.clear();
        root = newNode();
    }

    int newNode() {
        info.push_back(Mono::e());
        tag.push_back(Tag::e());
        lc.push_back(-1);
        rc.push_back(-1);
        return int(info.size()) - 1;
    }

    void pull(int p) {
        X left = (lc[p] != -1) ? info[lc[p]] : Mono::e();
        X right = (rc[p] != -1) ? info[rc[p]] : Mono::e();
        info[p] = Mono::op(left, right);
    }

    void apply(int p, int len, const Y& v) {
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
        int llen = len / 2;
        apply(lc[p], llen, tag[p]);
        apply(rc[p], len - llen, tag[p]);
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

    X rangeQuery(int p, int l, int r, int x, int y) {
        if (p == -1 || y <= l || r <= x) {
            return Mono::e();
        }
        if (x <= l && r <= y) {
            return info[p];
        }
        int mid = (l + r) / 2;
        push(p, r - l);
        return Mono::op(rangeQuery(lc[p], l, mid, x, y), rangeQuery(rc[p], mid, r, x, y));
    }
    X rangeQuery(int l, int r) {
        return rangeQuery(root, 0, n, l, r);
    }

    void rangeApply(int p, int l, int r, int x, int y, const Y& v) {
        if (y <= l || r <= x) {
            return;
        }
        if (x <= l && r <= y) {
            apply(p, r - l, v);
            return;
        }
        int mid = (l + r) / 2;
        push(p, r - l);
        rangeApply(lc[p], l, mid, x, y, v);
        rangeApply(rc[p], mid, r, x, y, v);
        pull(p);
    }
    void rangeApply(int l, int r, const Y& v) {
        rangeApply(root, 0, n, l, r, v);
    }

    template <typename F>
    int findFirst(int p, int l, int r, int x, int y, F&& pred) {
        if (p == -1 || y <= l || r <= x) {
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
        if (p == -1 || y <= l || r <= x) {
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
};

struct SumMono {
    struct Type {
        i64 v;
    };
    static Type e() {
        return {0};
    }
    static Type op(const Type& a, const Type& b) {
        return {a.v + b.v};
    }
    static Type from(const i64& x) {
        return {x};
    }
};

struct AddMono {
    struct Type {
        i64 k;
    };
    static Type e() {
        return {0};
    }
    static Type op(const Type& a, const Type& b) {
        return {a.k + b.k};
    }
};

struct ActMono {
    using Mono = SumMono;
    using Tag = AddMono;
    using X =  Mono::Type;
    using Y = Tag::Type;
    static X act(const X& x, const Y& y, int len) {
        return {x.v + y.k * len};
    }
};
