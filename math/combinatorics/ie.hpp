// cap(S) 表示 S 集合的交集大小

// 交集形式
template <typename T, typename F>
T ie(int n, F&& cap) {
    T ans{};
    for (int S = 1; S < (1 << n); S++) {
        T cur = cap(S);
        if (__builtin_popcount(S) & 1) {
            ans += cur;
        } else {
            ans -= cur;
        }
    }
    return ans;
}

// 补集形式
template <typename T, typename F>
T ieComp(int n, F&& cap) {
    T ans{};
    for (int S = 0; S < (1 << n); S++) {
        T cur = cap(S);
        if (__builtin_popcount(S) & 1) {
            ans -= cur;
        } else {
            ans += cur;
        }
    }
    return ans;
}

// 恰好满足 k 个性质的元素数量
template <typename T, typename F>
vector<T> ieExact(int n, F&& cap) {
    vector<T> N(n + 1, T{});
    for (int S = 0; S < (1 << n); S++) {
        int k = __builtin_popcount(S);
        N[k] += cap(S);
    }

    vector<T> binom(n + 2, T{}), E(n + 1, T{});
    binom[0] = T{1};
    for (int j = 0; j <= n; j++) {
        for (int k = 0; k <= j; k++) {
            T term = N[j] * binom[k];
            if ((j - k) & 1) {
                E[k] -= term;
            } else {
                E[k] += term;
            }
        }
        for (int k = j + 1; k >= 1; k--) {
            binom[k] += binom[k - 1];
        }
    }
    return E;
}

// 至少满足 k 个
template <typename T, typename F>
vector<T> ieLeast(int n, F&& cap) {
    auto E = ieExact<T>(n, cap);
    for (int k = n - 1; k >= 0; k--) {
        E[k] += E[k + 1];
    }
    return E;
}

// 至多满足 k 个
template <typename T, typename F>
vector<T> ieMost(int n, F&& cap) {
    auto E = ieExact<T>(n, cap);
    for (int k = 0; k < n; k++) {
        E[k + 1] += E[k];
    }
    return E;
}