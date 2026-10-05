#pragma once
#include <common.hpp>

vector<i64> buildDivisors(const vector<pair<i64, int>>& factors) {
    vector<i64> divisors = {1};
    for (auto& [p, e] : factors) {
        int sz = divisors.size();
        for (int i = 0; i < sz; i++) {
            i64 x = divisors[i];
            for (int j = 0; j < e; j++) {
                x *= p;
                divisors.push_back(x);
            }
        }
    }
    return divisors;
}
