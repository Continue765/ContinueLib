vector<int> toLehmer(vector<int>& p) {
    int n = p.size();
    Fenwick<Abel<int>> fen(n);
    vector<int> c(n);
    for (int i = n - 1; i >= 0; i--) {
        c[i] = fen.sum(p[i]);
        fen.add(p[i], 1);
    }
    return c;
}

vector<int> fromLehmer(vector<int>& c) {
    int n = c.size();
    vector<int> p(n);
    Fenwick<Abel<int>> fen(n);
    for (int i = 0; i < n; i++) {
        fen.add(i, 1);
    }
    for (int i = 0; i < n; i++) {
        p[i] = fen.kth(c[i]);
        fen.add(p[i], -1);
    }
    return p;
}

i64 toRank(vector<int>& p) {
    int n = p.size();
    auto c = toLehmer(p);
    i64 fac = 1, rk = 0;
    for (int i = n - 1; i >= 0; i--) {
        rk += c[i] * fac;
        fac *= (n - i);
    }
    return rk;
}

vector<int> fromRank(int n, i64 rk) {
    vector<int> c(n);
    for (int i = 1; i <= n; i++) {
        c[n - i] = rk % i;
        rk /= i;
    }
    return fromLehmer(c);
}