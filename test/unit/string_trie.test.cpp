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
    mt19937 rng(947);
    Trie randomTrie(20000);
    map<string, int> counts;
    for (int it = 0; it < 3000; ++it) {
        string word(rng() % 9, 'a');
        for (char& ch : word) ch += rng() % 26;
        if (it % 5 == 0 && !counts.empty()) word = counts.begin()->first;
        if (it % 3 != 0) {
            randomTrie.insert(word);
            ++counts[word];
        }
        assert(randomTrie.count(word) == counts[word]);
    }
    for (const auto& [key, count] : counts) {
        string word = key;
        assert(randomTrie.count(word) == count);
    }
    randomTrie.init(20000);
    for (const auto& [key, count] : counts) {
        string word = key;
        assert(randomTrie.count(word) == 0);
    }
}

int main() {
    test();
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
