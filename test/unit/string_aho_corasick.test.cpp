#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "string/aho_corasick.hpp"

void test() {
    AhoCorasick ac;
    vector<string> words = {"he", "she", "hers", "his"};
    vector<int> terminal;
    for (auto& word : words) terminal.push_back(ac.add(word));
    ac.work();
    assert(ac.len(terminal[0]) == 2 && ac.len(terminal[1]) == 3);
    assert(ac.link(terminal[1]) == terminal[0]);
    int state = 1;
    string text = "ahishers";
    vector<int> hits;
    vector<int> expected;
    for (int pos = 0; pos < static_cast<int>(text.size()); pos++) {
        state = ac.next(state, text[pos] - 'a');
        for (int i = 0; i < static_cast<int>(words.size()); i++) {
            if (text.substr(0, pos + 1).ends_with(words[i])) expected.push_back(i);
            int p = state;
            while (p > 1 && p != terminal[i]) p = ac.link(p);
            if (p == terminal[i]) hits.push_back(i);
        }
    }
    assert(hits == expected);
    assert(hits == vector<int>({3, 0, 1, 2}));
    ac.init();
    ac.work();
    assert(ac.size() == 2 && ac.next(1, 'a' - 'a') == 1);
}

int main() {
    test();
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
