#pragma once
#include <random/base.hpp>

template <typename T>
void shuffle(vector<T>& a) {
    int n = a.size();
    for (int i = 0; i < n; i++) {
        int j = randInt(0, i + 1);
        if (i != j) {
            swap(a[i], a[j]);
        }
    }
}
// OR ranges::shuffle(a, rng);

template <typename T>
T& randElem(vector<T>& a) {
    assert(!a.empty());
    return a[randInt(a.size())];
}

vector<i64> randArray(int n, i64 l, i64 r) {
    vector<i64> a(n);
    for (auto& x : a) {
        x = randInt(l, r);
    }
    return a;
}

vector<int> randPerm(int n) {
    vector<int> a(n);
    iota(a.begin(), a.end(), 0);
    shuffle(a);
    return a;
}

vector<i64> randDistinct(int n, i64 l, i64 r) {
    unordered_set<i64> s;
    vector<i64> a;
    for (i64 i = r - l - n; i < r - l; i++) {
        i64 x = randInt(i + 1);
        if (!s.insert(x).second) {
            s.insert(i), a.push_back(i + l);
        } else {
            a.push_back(x + l);
        }
    }
    shuffle(a);
    return a;
}
