#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "data_structure/binary_trie.hpp"

int main() {
    constexpr int bits = 31;
    BinaryTrie trie(1 + 9 * bits);
    multiset<int> values;
    for (int x : {0, 5, 5, 17, 1024, (1 << 30) + 3}) {
        trie.insert(x);
        values.insert(x);
    }
    auto check = [&](int x) {
        int expected = 0;
        for (int v : values) expected = max(expected, x ^ v);
        assert(trie.query(x) == expected);
    };
    for (int x : {0, 1, 5, 19, (1 << 30) + 9}) check(x);
    trie.erase(5);
    values.erase(values.find(5));
    trie.erase(0);
    values.erase(values.find(0));
    trie.insert(7);
    values.insert(7);
    for (int x : {0, 5, 7, 1023, (1 << 30)}) check(x);

    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
