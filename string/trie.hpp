#pragma once
#include <common.hpp>

struct Trie {
    struct Node {
        array<int, 26> nxt;
        int pass, end;

        Node() {
            nxt.fill(-1);
            end = 0;
            pass = 0;
        }
    };

    vector<Node> tr;
    int tot;

    Trie(int n) {
        init(n);
    }

    void init(int n) {
        tr.resize(n);
        tot = 0;
    }

    void insert(string& s) {
        int p = 0;
        ++tr[p].pass;
        for (char& ch : s) {
            int c = ch - 'a';
            if (tr[p].nxt[c] == -1) {
                ++tot;
                tr[p].nxt[c] = tot;
            }
            p = tr[p].nxt[c];
            ++tr[p].pass;
        }
        ++tr[p].end;
    }

    int count(string& s) {
        int p = 0;
        for (char& ch : s) {
            int c = ch - 'a';
            if (tr[p].nxt[c] == -1) {
                return false;
            }
            p = tr[p].nxt[c];
        }
        return tr[p].end;
    }
};
