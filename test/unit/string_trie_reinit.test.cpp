#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "string/trie.hpp"

void test() {
    Trie trie(32);
    string a = "abc", b = "ab";
    trie.insert(a);
    trie.init(32);
    // Reinitialization is expected to clear all paths and counters.
    assert(trie.count(a) == 0);
    trie.insert(b);
    assert(trie.count(b) == 1);
}

int main() {
    test();
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
