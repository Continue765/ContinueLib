struct Basis {
    array<i64, 64> p;

    Basis() {
        p.fill(0);
    }

    void insert(i64 x) {
        for (int i = 63; i >= 0; i--) {
            if (x >> i & 1) {
                if (!p[i]) {
                    p[i] = x;
                    return;
                }
                x ^= p[i];
            }
        }
    }

    bool check(i64 x) {
        for (int i = 63; i >= 0; i--) {
            if (x >> i & 1) {
                x ^= p[i];
            }
        }
        return x == 0;
    }

    i64 getMax() {
        i64 res = 0;
        for (int i = 63; i >= 0; i--) {
            res = max(res, res ^ p[i]);
        }
        return res;
    }

    i64 getMin() {
        for (int i = 0; i <= 63; i++) {
            return p[i];
        }
        return 0;
    }

    void gauss() {
        for (int i = 63; i >= 0; i--) {
            if (!p[i]) {
                continue;
            }
            for (int j = i - 1; j >= 0; j--) {
                if (p[i] >> j & 1) {
                    p[i] ^= p[j];
                }
            }
        }
    }

    i64 kth(int k) {
        vector<i64> basis;
        for (int i = 0; i <= 63; i++) {
            if (p[i]) {
                basis.push_back(p[i]);
            }
        }
        int r = basis.size();
        if (k > (1LL << r)) {
            return -1;
        }
        i64 res = 0;
        k--;
        for (int i = 0; i < r; i++) {
            if (k >> i & 1) {
                res ^= basis[i];
            }
        }
        return res;
    }
};