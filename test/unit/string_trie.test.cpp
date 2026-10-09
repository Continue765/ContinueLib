#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "string/trie.hpp"

void test() {
    Trie trie(64);
    string a = "", b = "a", c = "ab", d = "abc";
    trie.insert(a);
    trie.insert(b);
    trie.insert(c);
    trie.insert(c);
    assert(trie.count(a) == 1 && trie.count(b) == 1 && trie.count(c) == 2 && trie.count(d) == 0);
}

int main() {
    test();
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
