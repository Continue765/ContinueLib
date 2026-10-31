#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "combinatorics/ie.hpp"
#include "combinatorics/zeta.hpp"

void test() {
    vector<int> exact = ieExact<int>(3, [](int mask) { return 1 << (3 - popcount(static_cast<unsigned>(mask))); });
    assert(exact == vector<int>({1, 3, 3, 1}));
    assert(ieLeast<int>(3, [](int mask) { return 1 << (3 - popcount(static_cast<unsigned>(mask))); }) == vector<int>({8, 7, 4, 1}));
    assert(ieMost<int>(3, [](int mask) { return 1 << (3 - popcount(static_cast<unsigned>(mask))); }) == vector<int>({1, 4, 7, 8}));
    assert(ie<int>(3, [](int mask) { return 1 << (3 - popcount(static_cast<unsigned>(mask))); }) == 7);
    assert(ieComp<int>(3, [](int mask) { return 1 << (3 - popcount(static_cast<unsigned>(mask))); }) == 1);

    vector<int> f = {1, 2, 3, 4};
    auto originalF = f;
    subsetZeta(f);
    assert(f == vector<int>({1, 3, 4, 10}));
    subsetMobius(f);
    assert(f == originalF);
    supersetZeta(f);
    assert(f == vector<int>({10, 6, 7, 4}));
    supersetMobius(f);
    assert(f == originalF);

    mt19937 rng(401);
    for (int n = 0; n <= 6; ++n) {
        int size = 1 << n;
        for (int it = 0; it < 100; ++it) {
            vector<int> members(30), counts(n + 1), values(size);
            for (int& mask : members) {
                mask = rng() % size;
                ++counts[popcount(unsigned(mask))];
            }
            auto cap = [&](int subset) {
                return count_if(members.begin(), members.end(),
                    [&](int mask) { return (mask & subset) == subset; });
            };
            assert(ieExact<int>(n, cap) == counts);
            auto least = ieLeast<int>(n, cap), most = ieMost<int>(n, cap);
            for (int k = 0; k <= n; ++k) {
                assert(least[k] == accumulate(counts.begin() + k, counts.end(), 0));
                assert(most[k] == accumulate(counts.begin(), counts.begin() + k + 1, 0));
            }
            assert(ie<int>(n, cap) == int(members.size()) - counts[0]);
            assert(ieComp<int>(n, cap) == counts[0]);

            for (int& x : values) x = int(rng() % 21) - 10;
            vector<int> sub(size), sup(size);
            for (int mask = 0; mask < size; ++mask) {
                for (int other = 0; other < size; ++other) {
                    if ((mask & other) == other) sub[mask] += values[other];
                    if ((mask & other) == mask) sup[mask] += values[other];
                }
            }
            auto actual = values;
            subsetZeta(actual);
            assert(actual == sub);
            subsetMobius(actual);
            assert(actual == values);
            actual = values;
            supersetZeta(actual);
            assert(actual == sup);
            supersetMobius(actual);
            assert(actual == values);
        }
    }
}

int main() {
    test();
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
