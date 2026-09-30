template <typename Abel>
struct Fenwick {
    using X = typename Abel::Type;

    int n;
    vector<X> a;

    Fenwick(int _n) {
        init(_n);
    }

    void init(int _n) {
        n = _n;
        a.assign(n, Abel::e());
    }

    void add(int x, const X& v) {
        assert(0 <= x && x < n);
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] = Abel::op(a[i - 1], v);
        }
    }

    X sum(int x) {
        assert(0 <= x && x <= n);
        X res = Abel::e();
        for (int i = x; i > 0; i -= i & -i) {
            res = Abel::op(a[i - 1], res);
        }
        return res;
    }

    X rangeSum(int l, int r) {
        assert(l <= r);
        return Abel::op(Abel::inv(sum(l)), sum(r));
    }

    // lower_bound
    int kth(X k) {
        int x = 0;
        for (int i = 1 << __lg(n); i; i /= 2) {
            if (x + i <= n && k >= a[x + i - 1]) {
                x += i;
                k -= a[x - 1];
            }
        }
        return x;
    }
};

template <typename T>
struct Abel {
    using Type = T;
    static Type e() {
        return {0};
    }
    static Type op(const Type& a, const Type& b) {
        return {a + b};
    }
    static Type inv(const Type& a) {
        return {-a};
    }
};