#pragma once
#include <common.hpp>

struct BinaryTrie {
    struct Node {
        array<int, 2> ch;
        int end;
        Node() {
            ch[0] = ch[1] = 0;
            end = 0;
        }
    };

    vector<Node> tr;
    int tot;

    BinaryTrie(int n) {
        init(n);
    }

    void init(int n) {
        tr.resize(n);
        tot = 1;
    }

    void insert(int x) {
        int p = 1;
        for (int i = 30; i >= 0; i--) {
            int c = x >> i & 1;
            if (!tr[p].ch[c]) {
                ++tot;
                tr[p].ch[c] = tot;
            }
            p = tr[p].ch[c];
            tr[p].end++;
        }
    }

    int query(int x) {
        int p = 1, res = 0;
        for (int i = 30; i >= 0; i--) {
            int c = x >> i & 1;
            if (tr[p].ch[c ^ 1]) {
                res |= (1 << i);
                p = tr[p].ch[c ^ 1];
            } else {
                p = tr[p].ch[c];
            }
        }
        return res;
    }

    void erase(int x) {
        int p = 1;
        for (int i = 30; i >= 0; i--) {
            int c = x >> i & 1;
            int nxt = tr[p].ch[c];
            tr[nxt].end--;
            if (tr[nxt].end == 0) {
                 tr[p].ch[c] = 0;
            }
            p = nxt;
        }
    }
};
