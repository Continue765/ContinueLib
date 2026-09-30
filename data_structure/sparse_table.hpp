template <typename Band>
struct SparseTable {
    using X = typename Band::Type;

    int n;
    vector<vector<X>> st;

    SparseTable(const vector<X>& a) {
        init(a);
    }

    void init(const vector<X>& a) {
        n = a.size();
        int logn = __lg(n);
        st.assign(logn + 1, vector<X>(n));
        for (int i = 0; i < n; i++) {
            st[0][i] = a[i];
        }
        for (int j = 1; (1 << j) <= n; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[j][i] = Band::op(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    X query(int l, int r) {
        assert(l < r);
        int len = r - l;
        int t = __lg(len);
        return Band::op(st[t][l], st[t][r - (1 << t)]);
    }
};

template <typename T>
struct Band {
    using Type = T;
    static Type op(const Type& a, const Type& b) {
        return {max(a, b)};
    }
};